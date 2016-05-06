;; Comments?
;; List
'(This is a list)
(+ 1 1)
;;(xx)
;;(+ 1 a)
(next-line)
fill-column
(substring "hello" 0 2)
(message "hello, emacs lisp")
(message "hello, %s" (buffer-name))
(set 'msg (message "hello, %s" (buffer-name)))
msg
(set 'h "hello")
h
(set 'n '"world")
n
(buffer-name)
(buffer-file-name)
(current-buffer)
(message "current:\t%s\nrecent:\t%s" (current-buffer) (other-buffer))
(message "Current buffer size: %d" (buffer-size))
(message "Where is the point? %d" (point))
(message "Max point %d, min %d, point %d" (point-max) (point-min) (point))
(message "buffer size, point max, point cur: %d, %d %d"
         (buffer-size)
         (point-max)
         (point))
(font-family-list)
