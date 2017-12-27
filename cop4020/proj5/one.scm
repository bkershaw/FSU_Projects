;	mytrans.scm - student template for the project
;	Project 1 
;	micro-p to scheme converter
;
;	(eval (convert "filename") (the-environment))

(define test
	(lambda (filename)
		(let ((s-expr (convert filename)))
			(display s-expr)
			(newline)
			(eval s-expr)
			(newline)
		)
	)
)

(define file2list
	(lambda (filename)
		(begin	(set-current-input-port! (open-input-file filename))
			(read-list))))


(define read-list
	(lambda ()
		(let ((token (read)))
			(cond	((eof-object? token) '())
				(else (cons token (read-list)))))))

(define convert
	(lambda (filename)
		(begin	(set-current-input-port! (open-input-file filename))
			(statement (read)))))

(define statements
	(lambda ()
		(let (	(token (read)))
		(cond	((eof-object? token) '())
			((eq? token 'end) '())
			(else	(let* (	(s (statement token))
					(r (statements)))
				(cons s r)))))))

(define statement
	(lambda (token)
		(cond	((eq? token 'declare) (declare_statement))
			((eq? token 'begin) (begin_statement))
			((eq? token 'for) (for_statement))
			((eq? token 'if) (if_statement))
			((eq? token 'set) (set_statement))
			(else (expression token)))))

;; done
;; student template for begin_statement
;; BEGIN stmts END
;; assign s->statments just like declare_statement
(define begin_statement
	(lambda ()
		(let* (( s (statements)))
		  ( cons 'begin s))))


;; done found on page 6 of instructions
;; student template for declare_statement
(define declare_statement
	(lambda ()
		(let* ( (d (declarations))
		       (s (statements)))
		(cons 'let* (cons d s )))))


;; student template for for_statement
(define for_statement
	(lambda ()
		(let (( counter ( read)))
		  ( toexp (( read )))
		  ( setexp (statements( read)))
		  ( list 'for counter toexp setexp))))

;; student template for if_statement
;(define if_statement
;	(lambda ()
;            (let (( condition ( statements (read)))
;                   ( thenexpr ( statements (read)))
;                   ( elseexpr ( statements (read)))
;             ( list 'if condition thenexpr elseexpr )))))




(define declarations
	(lambda ()
		(let (	(token (read)))
		(cond	((eof-object? token) '(eof))
			((eq? token 'begin) '())
			(else	(let* (	(d (declaration token))
					(r (declarations)))
				(cons d r)))))))

(define declaration
	(lambda (token)
		(list token (expression (read-after '=)))))

(define read-after
	(lambda (token)
		(if (eq? (read) token)
			(read)
			(display "Syntax error"))))



;; got from last video
( define call_expression
         ( lambda ()
	   ( let ( ( token ( read )))
	     ( cons token (arguments)))))


;; got from last video
(define arguments
         ( lambda ()
	          ( let (( token ( read )))
		    (cond (( eq? token '$) '())
			   (( eof-object? token) '())
			   ( else ( let* (( e ( expression token ))
					 ( a ( arguments)))
				    ( cons e a )))))))

;; done found on page 9
;; student template for expression
(define expression
        (lambda (token)
            (if(eq? token 'call)(call_expression)
	       (token))))


;; student template for set statement
;; found on page 9
(define set_statement
	(lambda ()
            (let (( token (read)))
	      ( list 'set! token (expression (read-after '=))))))

