#lang racket

(print "hello, λ world")

(define (bin-oper-gen operator)
  (lambda (x y)
    (operator x y)))

(define (say-hi s)
  (if (string? s)
      (if (equal? (substring s 0 5) "hello")
          "hi"
          "huh?")
      "huh?"))

(say-hi 1)

(define (say-hi2 s)
  (if (and (string? s)
           (equal? (substring s 0 5) "hello"))
      "hi"
      "huh?"))

(say-hi 2)
(say-hi2 "hello Janny!")

((λ (x y) (+ x y)) 3 6)
(define (high i) (λ (j) (λ (k) (+ i j k))))
(define mid (high 1))
(define low (mid 2))
(low 3)
(low 100)
(define (foo operator)
  (let* ([x (random 10)]
        [o (random 10)])
    (operator x o)))

(foo +)
(foo -)

;; Recursion method
(define (my-length ls)
  (cond [(empty? ls) 0]
        [else (+ 1 (my-length (rest ls)))]))

(define (my-map f ls)
  (cond [(empty? ls) empty]
        [else (cons (f (first ls)) (my-map f (rest ls)))]))

;; Tail-recursion method
(define (my-length-tr ls)
  (define (iter l len)
    (cond [(empty? l) len]
          [else (iter (rest l) (+ 1 len))]))
  (iter ls 0))

(define (my-map-tr f ls)
  (define (iter l l-accum)
    (cond [(empty? l) (reverse l-accum)]
          [else (iter (rest l) (cons (f (first l) l-accum)))]))
  (iter ls empty))
