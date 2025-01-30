
;;; Separate out key names.
(setq last-kbd-macro
   (kmacro--keys (kmacro "M-\\ C-d M-f C-d <return>")))

(setq qmk-columns 16)
(defun qmk-insert-matrix (k)
  (insert (format "\"matrix\":[%d, %d], " (/ k qmk-columns) (mod k qmk-columns))))

;;; Replace key number with matrix position.
(setq last-kbd-macro
   (kmacro--keys (kmacro "C-k M-x e v a l - e x p r <return> ( q m k - i n s e r t - m a t r i x SPC # x C-y ) <return> C-f")))

;;; Insert matrix position.
(setq last-kbd-macro
   (kmacro--keys (kmacro "C-s \" x \" : C-b C-b C-b C-b C-x b <return> C-k C-f C-x b <return> C-y C-e C-f")))
