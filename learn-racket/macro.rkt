#lang racket

(define-syntax (foo x)
  (println x)
  #'(+ 1 1))

(define-syntax (s1 s)
  #'"hello, world")

(define g-stx #'"hehe")
g-stx

(define-syntax (s2 s)
  (println s)
  #'(eval 'g-stx))

