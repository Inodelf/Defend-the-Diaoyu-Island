;;git-emacs
;;支持emacs和外部程序的粘贴
(setq x-select-enable-clipboard t)
;;显示括号匹配
(show-paren-mode t)
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
 '(show-paren-mode t))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 )



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
(defun xwl-erc-text-matched-hook (match-type nickuserhost message)
  "Shows a growl notification, when user's nick was mentioned.
     If the buffer is currently not visible, makes it sticky."
  (when (and (erc-match-current-nick-p nickuserhost message)
             (not (string-match (regexp-opt '("Users"
                                              "User"
                                              "topic set by"
                                              "Welcome to "
                                              "nickname"
                                              "identified"
                                              "invalid"
                                              ))
                                message)))
    (let ((s (concat "ERC: " (buffer-name (current-buffer)))))
      (case system-type
        ((darwin)
         (xwl-growl s message))))))
 
(add-hook 'erc-text-matched-hook 'xwl-erc-text-matched-hook)
 
(defun xwl-growl (title message)
  (start-process "zenity" " zenity" growlnotify-command title "-a" "Emacs")
  (process-send-string " zenity" message)
  (process-send-string " zenity" "\n")
  (process-send-eof " zenity"))

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
