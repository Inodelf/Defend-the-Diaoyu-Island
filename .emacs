(setq x-select-enable-clipboard t)
(setq interprogram-paste-function 'x-cut-buffer-or-selection-value)

;; 显示列号
(setq column-number-mode t)
(setq line-number-mode t)
;;显示行号
;;(require 'linum)
;;(global-linum-mode t)

;;所有的备份文件都放置在~/backups目录下
(setq backup-directory-alist (quote (("." . "~/.backups"))))
(setq version-control t)
(setq kept-old-versions 2)
(setq kept-new-versions 5)
(setq delete-old-versions t)
(setq backup-directory-alist '(("." . "~/.backups")))
(setq backup-by-copying t)
;;emacs中，改变文件时，默认都会产生备份文件（以~结尾的文件）。可以完全去掉
;;（并不可取），也可以制定备份的方式。这里采用的是，把所有的文件备份都放在一个
;;固定的地方。对于每个备份文件，保留最原始的两个版本和最新的五个版本。
;;并且备份的时候，备份文件是复件，而不是原件。

;; 设置默认tab宽度为2
(setq tab-width 2
indent-tabs-mode t
c-basic-offset 2)

;; 语法高亮
(global-font-lock-mode t)

;; 显示括号匹配
(show-paren-mode t)
(setq show-paren-style 'parentheses)


;; 显示时间，格式如下
(display-time-mode 1)
(setq display-time-24hr-format t)
(setq display-time-day-and-date t)

(transient-mark-mode t)


(setq visible-bell t)
(setq inhibit-startup-message t)
(setq mouse-yank-at-point t)
(setq kill-ring-max 200)
(setq default-fill-column 60)
(setq-default indent-tabs-mode nil)
(setq default-tab-width 8)
(setq tab-stop-list ())
(setq sentence-end "\\([。！？]\\|……\\|[.?!][]\"')}]*\\($\\|[ \t]\\)\\)[ \t\n]*")
(setq sentence-end-double-space nil)
(setq enable-recursive-minibuffers t)
(setq scroll-margin 3
      scroll-conservatively 10000)
(setq default-major-mode 'text-mode)
(show-paren-mode t)
(setq show-paren-style 'parentheses)
(setq frame-title-format "emacs@%b")
(auto-image-file-mode)
(put 'set-goal-column 'disabled nil)
(put 'narrow-to-region 'disabled nil)
(put 'upcase-region 'disabled nil)
(put 'downcase-region 'disabled nil)
(put 'LaTeX-hide-environment 'disabled nil)
(setq version-control t)
(setq kept-new-versions 3)
(setq delete-old-versions t)
(setq kept-old-versions 2)
(setq dired-kept-versions 1)
(mapcar
 (function (lambda (setting)
	     (setq auto-mode-alist
		   (cons setting auto-mode-alist))))
 '(("\\.xml$".  sgml-mode)
   ("\\\.bash" . sh-mode)
   ("\\.rdf$".  sgml-mode)
   ("\\.session" . emacs-lisp-mode)
   ("\\.l$" . c-mode)
   ("\\.css$" . css-mode)
   ("\\.cfm$" . html-mode)
   ("gnus" . emacs-lisp-mode)
   ("\\.idl$" . idl-mode)))
(setq user-full-name "isolidot")
(setq user-mail-address "isolidot@gmail.com")

(setq dired-recursive-copies 'top)
(setq dired-recursive-deletes 'top)
(require 'xcscope)
(setq cscope-do-not-update-database t)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(display-time-mode t)
 '(show-paren-mode t))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )







;;;; CC-mode配置  http://cc-mode.sourceforge.net/
(require 'cc-mode)
(c-set-offset 'inline-open 0)
(c-set-offset 'friend '-)
(c-set-offset 'substatement-open 0)

;;;;我的C/C++语言编辑策略
 
(defun my-c-mode-common-hook()
  (setq tab-width 4 indent-tabs-mode nil)
  ;;; hungry-delete and auto-newline
  (c-toggle-auto-hungry-state 1)
  ;;按键定义
  (define-key c-mode-base-map [(control \`)] 'hs-toggle-hiding)
  (define-key c-mode-base-map [(return)] 'newline-and-indent)
  (define-key c-mode-base-map [(f7)] 'compile)
  (define-key c-mode-base-map [(meta \`)] 'c-indent-command)
  ;;  (define-key c-mode-base-map [(tab)] 'hippie-expand)
  (define-key c-mode-base-map [(tab)] 'my-indent-or-complete)
  (define-key c-mode-base-map [(meta ?/)] 'semantic-ia-complete-symbol-menu)

;;预处理设置
(setq c-macro-shrink-window-flag t)
(setq c-macro-preprocessor "cpp")
(setq c-macro-cppflags " ")
(setq c-macro-prompt-flag t)
(setq hs-minor-mode t)
(setq abbrev-mode t)
)
(add-hook 'c-mode-common-hook 'my-c-mode-common-hook)

;;;;我的C++语言编辑策略
(defun my-c++-mode-hook()
(setq tab-width 4 indent-tabs-mode nil)
(c-set-style "stroustrup")
;;  (define-key c++-mode-map [f3] 'replace-regexp)
)

(load-file "~/cedet-1.1/common/cedet.el")

(setq semanticdb-project-roots 
(list
(expand-file-name "/")))

(defun my-indent-or-complete ()
  (interactive)
  (if (looking-at "\\>")
      (hippie-expand nil)
    (indent-for-tab-command))
  )
 
 
(global-set-key [(control tab)] 'my-indent-or-complete)

(autoload 'senator-try-expand-semantic "senator")
 
(setq hippie-expand-try-functions-list
      '(
        senator-try-expand-semantic
        try-expand-dabbrev
        try-expand-dabbrev-visible
        try-expand-dabbrev-all-buffers
        try-expand-dabbrev-from-kill
        try-expand-list
        try-expand-list-all-buffers
        try-expand-line
        try-expand-line-all-buffers
        try-complete-file-name-partially
        try-complete-file-name
        try-expand-whole-kill
        )
      )

(global-set-key [(f5)] 'speedbar)
'(compile-command "make")
;;============================================================ 
;; git-emacs mode
;;------------------------------------------------------------
;(eval-when-compile (require 'cl))
;(setq git-state-modeline-decoration 'git-state-decoration-large-dot)
;(require 'git-emacs-autoloads)
;;------------------------------------------------------------
;;(require 'git-emacs)
(autoload 'mew "mew" nil t)
(autoload 'mew-send "mew" nil t)
 
;; Optional setup (Read Mail menu for Emacs 21):
(if (boundp 'read-mail-command)
    (setq read-mail-command 'mew))
 
;; Optional setup (e.g. C-xm for sending a message):



;;
;; coding setting
(setq locate-coding-system 'utf-8)
(set-terminal-coding-system 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-selection-coding-system 'utf-8)
(set-buffer-file-coding-system 'utf-8)
(set-clipboard-coding-system 'utf-8)
(prefer-coding-system 'utf-8)
;;
;; emacs-w3m
(require 'w3m-load)
(require 'mime-w3m)
(setq w3m-display-inline-image t)
(setq w3m-use-mule-ucs t)
(setq w3m-use-toolbar t)
(setq w3m-use-cookies t)
(setq w3m-tab-width 8)
(setq w3m-home-page "http://www.baidu.com")
(setq browse-url-browser-function 'w3m-browse-url)
(autoload 'w3m-browse-url "w3m" "www.baidu.com" t)
(global-set-key "\C-xm" 'browse-url-at-point)

;(autoload 'w3m "w3m" "Interface for w3m on Emacs." t)
;;
;; Mew
(autoload 'mew "mew" nil t)
(autoload 'mew-send "mew" nil t)
;; Mew Options
(setq read-mail-command 'mew)
(autoload 'mew-user-agent-compose "mew" nil t)
(if (boundp 'mail-user-agent)
    (setq mail-user-agent 'mew-user-agent))
(if (fboundp 'define-mail-user-agent)
    (define-mail-user-agent
       'mew-user-agent
       'mew-user-agent-compose
       'mew-draft-sent-message
       'mew-draft-kill
       'mew-send-hook))



(global-set-key [f11] 'my-fullscreen) ;; 启动全屏的快捷键
;全屏
(defun my-fullscreen ()
(interactive)
(x-send-client-message
nil 0 nil "_NET_WM_STATE" 32
'(2 "_NET_WM_STATE_FULLSCREEN" 0))
)
;最大化
(defun my-maximized ()
(interactive)
(x-send-client-message
nil 0 nil "_NET_WM_STATE" 32
'(2 "_NET_WM_STATE_MAXIMIZED_HORZ" 0))
(x-send-client-message
nil 0 nil "_NET_WM_STATE" 32
'(2 "_NET_WM_STATE_MAXIMIZED_VERT" 0))
)
(my-fullscreen) ;; 启动emacs时窗口最大化


(add-to-list 'load-path "~/wubi")

(require 'wubi)
(wubi-load-local-phrases) ; add user's Wubi phrases

(register-input-method
 "chinese-wubi" "utf-8" 'quail-use-package
 "WuBi" "WuBi"
 "wubi")

(if (< emacs-major-version 21)
    (setup-chinese-gb-environment)
  (set-language-environment 'utf-8))

(setq default-input-method "chinese-wubi")
;(require 'semantic-tag-folding nil 'noerror)  
;(global-semantic-tag-folding-mode 1)  
;(define-key semantic-tag-folding-mode-map (kbd "[f6]") 'semantic-tag-folding-fold-block)  
;(define-key semantic-tag-folding-mode-map (kbd "[f5]") 'semantic-tag-folding-show-block)   
;; 整个buffer所有函数折叠与展开  
;(define-key semantic-tag-folding-mode-map (kbd "[f9]") 'semantic-tag-folding-fold-all)  
;(define-key semantic-tag-folding-mode-map (kbd "[f8]") 'semantic-tag-folding-show-all)  

