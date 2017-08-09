;função principal a ser análizada
(defun funcao(x)
	( - (expt x 2) 3);f(x)= x^2-3
)

;função do méodo da bisseção
(defun bissecao(n a b)
	(setq medio (/ (+ a b) 2))
	(format t ">>: ~S~%" medio)
	(setq f_medip (funcao medio))
	(if(= f_medip 0) medio)
	(if(> (* f_medip (funcao a)) 0) (setq a medio) (setq b medio))
	(if(= (- n 1) 0) medio (bissecao (- n 1) a b))
)

;chamada de função
(format t "Resultado Final: ~S~%" (bissecao 10 0 4))
