REBOL [
]

context [
	internal_:	none
	api_:		none
	output_:	none
	env_:		none
	before_:	func [ code [ block! ] ][
		copy/deep compose/deep [
			func [ params [ block! ] ][
				(code)
			]
		]
	]
	run_: function [ code [ block! ] ] [ c ] [
		c: compose [(code)]
		copy/deep compose/deep [
			func [ params [ block! ] ][
				before params
				
				bind c env
				bind c api
				bind c output
				do c
				
				after params
			]
		]
	]
	after_:	func [ code [ block! ] ][
		copy/deep compose/deep [
			func [ params [ block! ] ][
				(code)
			]
		]
	]
	private:	copy []
	public:		copy []

	set 'feature func [ 		;'
		'name 					;'
		content [ block! ] 
	][
		do content
		set name make object! [ 
			version:	none
			output:		none
			env:		none
			api: 		none 
			main:		none
			run: 		none 
			bind private self
			context internal_: private 
			bind internal_ self/env
		]
		clear private
	]
	
	set 'output func [ data [ block! ] ][				;'
		;repend private [ 'set to lit-word! 'output_ to set-word! 'output make object! data ]	;'
		append private compose [ set (to lit-word! 'output_) set (to lit-word! 'output) (make object! data) ] 
	]

	set 'env func [ data [ block! ] ][					;'
		; repend private [ to set-word! 'env make object! data ]		;'
		append private compose [ set (to lit-word! 'env_) set (to lit-word! 'env) (make object! data) ] 
	]

	set 'internal func [ code [ block! ] ][				;'
		;repend private [ to set-word! 'internal make object! code ]	;'
		append private code
	]

	set 'api func [ code [ block! ] ][				;'
		api_: code
		append private compose [ set (to lit-word! 'api) ]	;'
		append private compose/deep [ make object! bind [ (code) ] output_ ]
	]

	set 'version func [ value [ tuple! string! ] ][		;'
		append private compose [ set (to lit-word! 'version) ]	;'
		append private compose/deep [ (value) ]
	]
	
	set 'before func [ code [ block! ] ][				;'
		append private to set-word! 'before				;'
		append private before_ code
	]

	set 'after func [ code [ block! ] ][				;'
		append private to set-word! 'after				;'
		append private after_ code
	]

	set 'main func [ code [ block! ] ][					;'
		append private compose [ set (to lit-word! 'main) ]	;'
		append/only private code
		; create run function
		append private compose [ set (to lit-word! 'run) ]	;'
		append private run_ code
	]
]
