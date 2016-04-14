#lang slideshow
(define (square n)
  (filled-rectangle n n))

(define (four p)
  (define two-p (hc-append p p))
  (vc-append two-p two-p))

(define (checker p1 p2)
  (let ([p12 (hc-append p1 p2)]
        [p21 (hc-append p2 p1)])
    (vc-append p12 p21)))

(define (checkerboard p)
  (let* ([rp (colorize p "red")]
         [bp (colorize p "black")]
         [c (checker rp bp)]
         [c4 (four c)])
    (four c4)))

(define (series mk)
  (hb-append 4 (mk 10) (mk 20) (mk 30) (mk 20) (mk 10)))

(define (rgb-series mk)
    (vc-append
     (series (lambda (sz) (colorize (mk sz) "red")))
     (series (lambda (sz) (colorize (mk sz) "green")))
     (series (lambda (sz) (colorize (mk sz) "blue")))))

(define (rgb-maker mk)
    (lambda (sz)
      (vc-append (colorize (mk sz) "red")
                 (colorize (mk sz) "green")
                 (colorize (mk sz) "blue"))))

