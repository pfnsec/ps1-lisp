
(map 
  (lambda (x)
    (* 10 x))
  (1 2 3 4 5))


(define is-3
  (lambda (x)
    (if (= x 3)
      1
      0)))

(map is-3 (3 4 3 2))


(fact 10)

(define fact 
  (lambda (x)
    (if (= x 1)
      x
      (* x (fact (- x 1))))))

(if (> x 2)
  (+ (- (* x x) x) 4)
  (if (and (or (> x 1) (= x 1)) (or (< x 2) (= x 2)))
      (/ 1 x)
      0))
