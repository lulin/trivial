#lang racket

;; regexp value: #rx

;; regexp-quote
(regexp-quote ".")

(regexp-match? #rx"." "a")

(regexp-match #rx"\\." "a.")
(regexp-match #rx"a.+[:space:]+" "abc ade aaa")
