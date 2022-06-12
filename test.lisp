
(+ 3 3 3 3)

(defun (fact x)
  (if (= x 1)
    x
    (* x (fact (- x 1)))))

(if (> x 2)
  (+ (- (* x x) x) 4)
  (if (and (or (> x 1) (= x 1)) (or (< x 2) (= x 2)))
      (/ 1 x)
      0))
