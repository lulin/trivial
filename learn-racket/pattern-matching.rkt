#lang racket
(require racket/match)

;; match equal? value
(match '(1 2)
  [(list 1 2) (println "matched!") #t]
  [- #f])

(struct sa (x y))

(match (sa 1 2)
  [(sa x y) (let ([oa (sa x y)]) (sa-x oa)) ]
  [_ #f])
