;; 1.
(defun f(x)
    (if (evenp x) 
        x 
        (+ x 1) ))
;(print (f 2))


;; 2.
(defun f(x)
    (if (> x 0) 
        (+ x 1) 
        (- x 1) ))
;(print (f -2))


;; 3.
(defun f(x y)
    (if (< x y) 
        (list x y) 
        (list y x) ))
;(print (f -2 -5))


;; 4.
(defun f(x y z)
    (if (or (and (> x y) (< x z))
            (and (< x y) (> x z))) 
        T
        NIL ))
;(print (f -4 6 -5))


;; 5.
;(print (and 'fee 'fie 'foe) )
;(print (or nil 'fie 'foe)  )
;(print (and (equal 'abc 'abc) 'yes)  )
;(print (or 'fee 'fie 'foe) )
;(print (and nil 'fie 'foe) )
;(print (or (equal 'abc 'abc) 'yes))


;; 6.
(defun p(x y)
    (>= x y) )
;(print (p -4 -6))


;; 7.
(defun pred1 (x) 
(and (numberp x) (plusp x)))   
    
(defun pred2 (x)
(and (plusp x)(numberp x)))
;(print (pred2 'a))


;; 8.

(defun f (x y z)
    (if (> x y) 
        (< x z)
        (if (< x y) 
            (> x z)) ))
;(print (f 4 6 5))

(defun f (x y z)
    (cond ((> x y) (< x z))
          ((< x y) (> x z)) ))
;(print (f 4 6 5))

(defun f (x y z)
    (or (and (> x y) (< x z))
        (and (< x y) (> x z))))
;(print (f 4 6 5))

;; 9.
(defun how_alike(x y)
    (cond ((or  (= x y) (equal x y)) 'the_same)
          ((and (oddp x) (oddp y))   'both_odd) 
          ((and (evenp x) (evenp y)) 'both_even) 
          (t 'difference)))

;(print (how_alike 4 6))

(defun how_alike(x y)
    (if (if (= x y) T (if (equal x y) T NIL)) 'the_same 
    (if (if (oddp x) (if (oddp y) T NIL) NIL)   'both_odd 
    (if (if (evenp x) (if (evenp y) T NIL) NIL) 'both_even 
     'difference))))
;(print (how_alike 4 6))

(defun how_alike(x y)
    (or (and (or  (= x y) (equal x y)) 'the_same)
        (and (and (oddp x) (oddp y))   'both_odd)
        (and (and (evenp x) (evenp y)) 'both_even)
        'difference))
;(print (how_alike 3 5))

(defun how_alike(x y) 
    (cond ((= x y) 'the_same) ((equal x y) 'the_same)
    ((cond ((oddp x) (cond ((oddp y) 'both_odd)))))
    ((cond ((evenp x) (cond ((evenp y) 'both_even)))))
        (T 'difference)))