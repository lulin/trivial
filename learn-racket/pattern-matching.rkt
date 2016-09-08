#lang racket
(require racket/match)

;; match equal? value
(match '(1 2)
  [(list 1 2) (println "matched!") #t]
  [- #f])
