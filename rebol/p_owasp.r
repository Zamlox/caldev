REBOL [
]

do %/usr/local/bin/scripts/shell.r
do %/usr/local/bin/scripts/db.r
do %feature.r

context [
	feature dtrack-upgrade [
		version 1.0.0
		
		; --- feature output data
		; --- define output before api otherwise api cannot find words from output only by name.
		output [
			components: none
		]
		; --- feature local data
		env [
			db: 		none
			dbs:		copy []
			from-db: to-db: none
			dtrack-api-key:	"hkyDgiEL2lS5TBbA02UIzpx20lu9Jrlp"
			projects:	none
			comp-file:	none
		]
		
		; --- feature api
		api [
			get-components: func [
				db 				[ object! ]
				project-name	[ string! ]
				version			[ string! ]
				/local project-data project-id components-ids di dtrack i
			][
				project-data: get-project db project-name version
				if all [
					project-data
					project-id: project-data/1
				][
					components-ids: get-dependencies db project-id
					if components-ids [
						components: get-components-data db components-ids
					]
				]
				components
			]
			
			serialize: func [
				data 	[ block! ]
			][
				save-to-json data
			]
			
			add-bom: func [
				db			[ object! ]
				proj-name	[ string! ]
				proj-vers	[ string! ]
				file		[ file! ]
				/local command proj-data proj-uuid
			][
				proj-data: get-project db proj-name proj-vers
				either all [
					proj-data
					proj-uuid: proj-data/2
				][
				{
					command: get-bom-command proj-uuid file
					print command
					shell/run command
				}
				][
					print rejoin [ "ERROR !!! Project '" proj-name "' or version '" proj-vers "' does not exist in database '" db/db-name "'"]
				]
			]
			
		]
		
		; --- executed before main
		before [
			clear env/dbs
			foreach [ from db-name-from to db-name-to ] params [
				; check syntactic sugar
				if from <> 'from [		;'
					print [ "ERROR !!! Invalid keyword used:" from newline "Keyword allowed: from"]
					halt
				]
				if to <> 'to [		;'
					print [ "ERROR !!! Invalid keyword used:" to newline "Keyword allowed: to"]
					halt
				]
				; db from
				env/db: make-db db-name-from
				append env/dbs env/db
				env/db/connect
				env/from-db: env/db
				; db to
				env/db: make-db db-name-to
				append env/dbs env/db
				env/db/connect
				env/to-db: env/db
			]
		]
		; --- executed after main
		after [
			foreach db env/dbs [
				db/disconnect
			]
			clear env/dbs
		]
		; --- main execution point of feature
		main [
			comp-file: %components.json
			projects: [
				;"B450"	"2.0.8"
				;"B650"	"2.0.8"
				;"B850"	"2.0.8"
				;"EMBC"	"2.0.8"
				;"B450"	"2.4"
				;"B650"	"2.4"
				;"B850"	"2.4"
				;"EMBC"	"2.4"
				;"Mobile Care Server"	"6.3-7"
			]
			foreach [ project version ] projects [
				write comp-file serialize get-components from-db project version
				;add-bom to-db project version comp-file
			]
		]
		
		; --- internal implementation
		internal [
			make-db: func [ dbname ][
				make pg-db! [
					server:		"172.18.0.3"
					user:		"dtrack"
					pwd:		"qwertyuiop"
					db-name: 	dbname
				]
			]
			
			get-project: func [
				db 		[ object! ]
				name	[ string! ]
				version	[ string! ]
				/local result db-res sql 
			][
				result: none
				; get project id
				sql: rejoin [{SELECT "ID", "UUID" FROM public."PROJECT" WHERE "NAME" like '} name {' AND "VERSION"='} version {'}]
				; print sql
				unless empty? db-res: copy db/run sql [
					result: repend copy [] [ db-res/1/1 db-res/1/2 ]
				]
				result
			]
			
			get-dependencies: func [
				db 			[ object! ]
				project-id	[ integer! ]
				/local db-res sql
			][
				sql: rejoin [{SELECT "COMPONENT_ID" FROM public."DEPENDENCY" WHERE "PROJECT_ID"=} project-id]
				db-res: copy db/run sql 
			]
			
			get-components-data: func [
				db 				[ object! ]
				components-ids	[ block! ]
				/local result db-res sql
			][
				result: copy []
				foreach row components-ids [
					sql: rejoin [{SELECT "DESCRIPTION", "NAME", "CPE", "VERSION" FROM public."COMPONENT" WHERE "ID"=} row/1]
					unless empty? db-res: copy db/run sql [
						repend result [
							either none? db-res/1/1 [""][db-res/1/1]
							"false"			; modified
							either none? db-res/1/2 [""][db-res/1/2]
							either none? db-res/1/3 [""][db-res/1/3]
							"library"		; type
							either none? db-res/1/4 [""][db-res/1/4]
						]
					]
				]
				result
			]

			escape-text: func [ text [ string! ] ][
				replace/all text "{" #"^(7B)" 
				replace/all text "}" #"^(7D)" 
			]
			
			save-to-json: func [
				data	[ block! ]
				/local content
			][
				content: rejoin [
#"^(7B)"
{
	"bomFormat": "CycloneDX",
	"components": [
}
				]
				foreach  [description modified name cpe libname version] data [
					content: rejoin [
						content
tab tab #"^(7B)"
{
			"description": "} escape-text description {",
			"modified": "} modified {",
			"name": "} name {",
			"cpe": "} cpe {",
			"type": "} libname {",
			"version": "} version {"
}
tab tab #"^(7D)" {,} newline
					]
				]
				remove/part find/reverse tail content "," 1
				content: rejoin [
					content
tab {]} newline
#"^(7D)"
				]
			]
			
			get-bom-command: func [
				project-uuid	[ string! ]
				file			[ file! ]
			][
				rejoin [ "curl -v --noproxy '*' -H 'X-API-Key: " dtrack-api-key "' -H 'Content-Type: multipart/form-data; charset=utf-8; boundary=__X_BOM_BOUNDARY__' -F 'project=" project-uuid "' -F 'bom=@" file "' http://172.18.0.10:8080/api/v1/bom" ]
			]
		]
	]
]

dtrack-upgrade/run [ 
	from "dtrack_361" to "dtrack_4xx" 
]
