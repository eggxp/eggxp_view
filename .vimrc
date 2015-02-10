syntax on

source $VIMRUNTIME/vimrc_example.vim
"source $VIMRUNTIME/mswin.vim
"behave mswin



"color darkblue
set encoding=utf-8
set fileencoding=utf-8
set fileencodings=utf-8
set termencoding=utf-8
set noswapfile
set tags=tags;
set nolist

set number


set nocompatible
set tabstop=2
set softtabstop=2
set expandtab


set shiftwidth=2
set nobackup
set nowritebackup
set ambiwidth=double
set sts=2
colorscheme torte
set ignorecase smartcase

:map <F12> :!python.exe %

:map <F2> :silent! %s/\s\+$//<ENTER>
