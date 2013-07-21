;;在emacs里使用scheme   
;; Also highlight parens   
(setq show-paren-delay 0  
   show-paren-style 'parenthesis)
;; This is the binary name of my scheme implementation   
(setq scheme-program-name "mit-scheme")  
;;auto complete配置
(require 'auto-complete-config)
(add-to-list 'ac-dictionary-directories "/usr/share/emacs/site-lisp/ac-dict")
(ac-config-default)
;;颜色配置
(add-to-list 'load-path "~/.emacs.d/")
(require 'color-theme)
(color-theme-initialize)
(color-theme-comidia)
(set-background-color "black") ;; 使用黑色背景
(set-foreground-color "white") ;; 使用白色前景
(set-face-foreground 'region "green")  ;; 区域前景颜色设为绿色
(set-face-background 'region "blue") ;; 区域背景色设为蓝色
;;git-emacs
;;支持emacs和外部程序的粘贴
(setq x-select-enable-clipboard t)
;;显示括号匹配
(show-paren-mode t)
;;先用光标定位，然后鼠标中键点击
(setq mouse-yank-at-point t)
;;防止页面滚动时跳动， scroll-margin 3 可以在靠近屏幕边沿3行时就开始滚动，可以很好的看到上下文。
(setq scroll-margin 3
      scroll-conservatively 10000)
;;把fill-column设为80
(setq default-fill-column 80)
;;org-mode下的自动换行
(add-hook 'org-mode-hook (lambda () (setq truncate-lines nil))) 
;;递归使用minibuffer
(setq enable-recursive-minibuffers t)
;;显示时间格式
(display-time-mode 1)
(setq display-time-24hr-format t)
(setq display-time-day-and-date t)
;;显示行列
(column-number-mode t)
;;显示行号
(global-linum-mode t)
;;禁用启动信息
(setq inhibit-startup-message t)
;;语法高亮
(global-font-lock-mode t)
;;打开图片显示功能
(auto-image-file-mode t)
;;读取或写入文件的编码方式
(setq file-name-coding-system 'utf-8)
;;高亮显示选中的区域
(transient-mark-mode t)
;;设置个人信息
(setq user-full-name "mordory")
(setq user-mail-address "isolidot@gmail.com")
;;光标靠近鼠标时，让鼠标指针自盍让开
(mouse-avoidance-mode 'animate)
;;设置 sentence-end 可以识别中文标点。不用在 fill 时在句号后插 入两个空格
(setq sentence-end "\\([。！？]\\|……\\|[.?!][]\"')}]*\\($\\|[ \t]\\)\\)[ \t\n]*")
(setq sentence-end-double-space nil)
;;把缺省的 major mode 设置为 text-mode, 而不是几乎什么功能也 没有的 fundamental-mode. 
(setq default-major-mode 'text-mode)
;;在标题栏显示buffer的名字，而不是 emacs@wangyin.com 这样没用的提示
(setq frame-title-format "%b")
;;一个简单的办法设置 auto-mode-alist, 免得写很多 add-to-list. 
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

;;在emacs中添加约会提醒
(setq appt-issue-message t)
;;git-emacs
(add-to-list 'load-path "~/git-emacs/")
(require 'git-emacs)

(require 'xcscope)
(add-to-list 'auto-mode-alist '("\\.org$" . org-mode))
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(display-time-mode t)
 '(show-paren-mode t)
 '(truncate-partial-width-windows nil))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 )
(setq org-todo-keywords
    '((sequence "TODO(t!)" "NEXT(n)" "WAITTING(w)" "SOMEDAY(s)" "|" "DONE(d@/!)" "ABORT(a@/!)")
     ))  
;;可以定义org-remember命令的快捷键，比如C-c c(这个快捷键应该是org菜单中最快捷的)
(define-key global-map "\C-cc" 'org-remember)
;;org-mode不同文件之间的移动
   '(org-refile-targets (quote (("newgtd.org" :maxlevel . 1)                                                                                             
                               ("someday.org" :level . 2))))
;;org-remember的模板配置
(org-remember-insinuate) (setq org-directory "~/Documents/Dropbox/0.GTD/") (setq org-remember-templates '(("New" ?n "* %? %t \n %i\n %a" "~/Documents/Dropbox/0.GTD/inbox.org" ) ("Task" ?t "** TODO %?\n %i\n %a" "~/Documents/Dropbox/0.GTD/task.org" "Tasks") ("Calendar" ?c "** TODO %?\n %i\n %a" "~/Documents/Dropbox/0.GTD/task.org" "Tasks") ("Idea" ?i "** %?\n %i\n %a" "~/Documents/Dropbox/0.GTD/task.org" "Ideas") ("Note" ?r "* %?\n %i\n %a" "~/Documents/Dropbox/0.GTD/note.org" ) ("Project" ?p "** %?\n %i\n %a" "~/Documents/Dropbox/0.GTD/project.org" %g) )) (setq org-default-notes-file (concat org-directory "/inbox.org"))
;;emacs的日程表快捷键
(define-key global-map "\C-ca" 'org-agenda)

;;以下是erc的配置
;;默认编码
(setq erc-default-coding-system '(utf-8 . utf-8))
;;设置nick和全名
(setq erc-nick "mordory"
      erc-user-full-name "mordory")
;;登录后自加入的channels
(erc-autojoin-mode 1)
(setq erc-autojoin-channels-alist
      '(("oftc.net"
	 "#ubuntu-cn")))

;;关键信息高亮
(erc-match-mode 1)
(setq erc-keywords '("emacs" "org-mode"))
(setq erc-pals '("rms"))

;;屏蔽的消息
(setq erc-ignore-list nil)
(setq erc-hide-list
      '("JOIN" "PART" "QUIT" "MODE"))

;;新消息提醒
;(defun xwl-erc-text-matched-hook (match-type nickuserhost message)
;  "Shows a growl notification, when user's nick was mentioned.
;     If the buffer is currently not visible, makes it sticky."
;  (when (and (erc-match-current-nick-p nickuserhost message)
;             (not (string-match (regexp-opt '("Users"
;                                              "User"
;                                              "topic set by"
;                                              "Welcome to "
;                                              "nickname"
;                                              "identified"
;                                              "invalid"
;                                              ))
;                                message)))
;    (let ((s (concat "ERC: " (buffer-name (current-buffer)))))
;      (case system-type
;        ((darwin)
;         (xwl-growl s message))))))
 
;(add-hook 'erc-text-matched-hook 'xwl-erc-text-matched-hook)
 
;(defun xwl-growl (title message)
;  (start-process "zenity" " “zenity --notification --text message" "Emacs")
;  (process-send-string " zenity" message)
;  (process-send-string " zenity" "\n")
;  (process-send-eof " zenity"))

;;只能在emacs-24以后用的ERC提醒配置
(require 'notifications)  
(defun erc-global-notify (match-type nick message)  
  "Notify when a message is recieved."  
  (notifications-notify  
   :body message  
   :title (car (split-string nick "!"))  
   :urgency 'normal))  
(add-hook 'erc-text-matched-hook 'erc-global-notify) 

;;时间戳
(erc-timestamp-mode 1)
;;时间戳显示方式
(setq erc-insert-timestamp-function 'erc-insert-timestamp-left)
;;记录log
(require 'erc-log)
(erc-log-mode 1)
(setq erc-log-channels-directory "~/var/erc/"
      erc-save-buffer-on-part t
      erc-log-file-coding-system 'utf-8
      erc-log-write-after-send t
      erc-log-write-after-insert t)
 
(unless (file-exists-p erc-log-channels-directory)
  (mkdir erc-log-channels-directory t))


;;emacs-w3m
;load & init 
(autoload 'w3m "w3m" "interface for w3m on emacs" t)
(autoload 'w3m-browse-url "w3m" "Ask a WWW browser to show a URL." t)
(autoload 'w3m-search "w3m-search" "Search words using emacs-w3m." t)

;settings
(setq w3m-use-cookies t)
(setq w3m-home-page "http://www.google.com")

(require 'mime-w3m) 
(setq w3m-default-display-inline-image t) 
(setq w3m-default-toggle-inline-images t)
