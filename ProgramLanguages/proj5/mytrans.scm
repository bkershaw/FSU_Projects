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



;; student template for begin_statement
(define begin_statement
	(lambda ()
		'()))

;; student template for declare_statement
(define declare_statement
	(lambda ()
		'()))

;; student template for for_statement
(define for_statement
	(lambda ()
		'()))

;; student template for if_statement
(define if_statement
	(lambda ()
		'()))


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

;; student template for expression
(define expression
        (lambda (token)
            '()))

;; student template for expression
(define set_statement
	(lambda ()
            '()))
