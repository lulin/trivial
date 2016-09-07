#lang racket

;; define a syntax transformer
(define-syntax (foo stx)
  #'(displayln "hehe"))

;; define a syntax object with 'define'
(define g-stx #'(displayln "hehe"))

;; Convert a syntax object to S-exp
(syntax->datum g-stx)
(eval (syntax->datum g-stx))

(define (is-pair? e)
  (match e
    [empty "yes"]
    [(cons x null) #t]
    [_ #f]))
