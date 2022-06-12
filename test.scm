(load-option 'format)

(define source
  (open-input-file "test.lisp"))

(define top 
  (read source))

(define (evaluate expr)
  (if (pair? expr)
      (begin 
       (display "CONS(")
       (display (evaluate (car expr)))
       (display ", ")
       (display (evaluate (cdr expr)))
       (display ")"))
      (cond 
        ((null? expr)
          (begin
           (display "NIL")))
        ((number? expr)
          (begin
           (display 
             (format #f "WORD(~A)" expr))))
        (#t
          (begin
           (display 
             (format #f "SYMBOL(\"~A\")" expr))))))
    "")



(newline)
(display "#include \"cons.h\"")
(newline)
(evaluate top)
(quit)
