#lang racket

(define (fib-recursive n)
  (cond [(or (eq? n 1) (eq? n 2)) 1]
        [else (+ (fib-recursive (- n 1)) (fib-recursive (- n 2)))]))

(define (fib-iter n)
  (define (iter i accum1 accum2)
    (if (> i n)
        accum1
        (iter (+ i 1) (+ accum1 accum2) accum1)))
  (if (n . < . 3)
      1
      (iter 3 1 1)))
