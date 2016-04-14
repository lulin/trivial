#lang planet neil/sicp

(define (square x) (* x x))
(define (sum-of-square x y) (+ (square x) (square y)))
(define ss sum-of-square)

;;;;

;; Exercise 1.3: Define a procedure that takes three numbers as arguments and
;; returns the sum of the squares of the two larger numbers

(define (bigger-squares-sum x y z)
  (if (> x y)
      (if (> y z) (ss x y)
          (ss x z))
      (if (> x z) (ss x z)
          (ss y z))))
(define e1.3 bigger-squares-sum)

;; Square roots, by Newton's Method

(define (average x y) (/ (+ x y) 2))

(define (improve-guess guess x) (average guess (/ x guess)))

(define (precise-enough? x y p)
  (< (abs (- x y)) p))

;; Square roots iterator
(define (sqrt-iter guess x precise)
  (if (precise-enough? guess (improve-guess guess x) precise)
      guess
      (sqrt-iter (improve-guess guess x) x precise)))

;; Square roots
(define (sqrt x) (sqrt-iter 1.0 x 0.0000000001))

;; new-if
(define (new-if predicate then-clause else-clause)
  (cond (predicate then-clause)
        (else else-clause)))

;;;; Cube roots

(define (cube-root x)
  (cube-root-iter 1.0 x 0.00001))
  
(define (cube-root-iter a x precise)
  (if (precise-enough? a (improve-cube-a a x) precise)
      a
      (cube-root-iter (improve-cube-a a x) x precise)))

;; improve cube roots approximation
(define (improve-cube-a a x)
  (/ (+ (/ x (square a)) (* 2 a)) 3))