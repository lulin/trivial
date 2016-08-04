#lang racket

(define (m-for/list-01 fn lst)
  (define (iter l accum)
    (if (null? l)
        (reverse accum)
        (iter (cdr l) (cons (fn (car l)) accum))))
  (iter lst null))
