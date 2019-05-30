set nocompatible              " 去除VI一致性
filetype off                  
set rtp+=~/.vim/bundle/Vundle.vim   " 设置包括vundle和初始化相关的runtime path
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'   " 让vundle管理插件版本,必须
Plugin 'w0rp/ale'   "ale语法检查
Plugin 'Valloric/YouCompleteMe' "YCM代码补全
Plugin 'vim-scripts/winmanager' "文件管理器
Plugin 'vim-scripts/taglist.vim'    "标签视图
Plugin 'sickill/vim-monokai'    "主题
Plugin 'vim-airline/vim-airline'    "airline 状态栏
Plugin 'vim-airline/vim-airline-themes'
Plugin 'Chiel92/vim-autoformat' "代码格式化插件
Plugin 'Yggdroot/indentLine'    "缩进指示线
Plugin 'kien/ctrlp.vim'     "文件搜索
Plugin 'vim-scripts/matchit.zip'    "标签匹配跳转
Plugin 'jiangmiao/auto-pairs'       "括号补全、引号补全
call vundle#end()
filetype plugin indent on    " 加载vim自带和插件相应的语法和文件类型相关脚本

" ALE
"使用键【\】作为leader
let mapleader="\\" 
" 设置状态栏
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")}\ %{ALEGetStatusLine()}
"始终开启标志列
"let g:ale_sign_column_always = 1
let g:ale_set_highlights = 0
"自定义error和warning图标
let g:ale_sign_error = 'x'
let g:ale_sign_warning = '!'
"在vim自带的状态栏中整合ale
let g:ale_statusline_format = ['x %d', '! %d', '✔ OK']
"显示Linter名称,出错或警告等相关信息
let g:ale_echo_msg_error_str = 'x'
let g:ale_echo_msg_warning_str = '!'
let g:ale_echo_msg_format = '[%linter%] %s [%severity%]'
"普通模式下，sp前往上一个错误或警告，sn前往下一个错误或警告
nmap sp <Plug>(ale_previous_wrap)
nmap sn <Plug>(ale_next_wrap)
"<Leader>s触发/关闭语法检查
nmap <Leader>s :ALEToggle<CR>
"<Leader>d查看错误或警告的详细信息
nmap <Leader>d :ALEDetail<CR> 
"文件内容发生变化时不进行检查
let g:ale_lint_on_text_changed = 'never'
"打开文件时不进行检查
let g:ale_lint_on_enter = 0
"使用clang对c和c++进行语法检查，对python使用pylint进行语法检查
let g:ale_linters = {
\   'c++': ['clang'],
\   'c': ['clang'],
\   'python': ['pylint'],
\}

" YouCompleteMe
"配置默认文件路径
let g:ycm_global_ycm_extra_conf = '~/.ycm_extra_conf.py'
"打开vim时不再询问是否加载ycm_extra_conf.py配置
let g:ycm_confirm_extra_conf = 0
set completeopt=longest,menu
"自动开启语义补全
let g:ycm_seed_identifiers_with_syntax = 1
"在注释中也开启补全
let g:ycm_complete_in_comments = 1
let g:ycm_collect_identifiers_from_comments_and_strings = 0
"字符串中也开启补全
let g:ycm_complete_in_strings = 1
let g:ycm_collect_identifiers_from_tags_files = 1
"开启基于tag的补全，可以在这之后添加需要的标签路径  
let g:ycm_collect_identifiers_from_tags_files = 1
"开始补全的字符数
let g:ycm_min_num_of_chars_for_completion = 2
"补全后自动关闭预览窗口
let g:ycm_autoclose_preview_window_after_completion = 1
"禁止缓存匹配项,每次都重新生成匹配项
let g:ycm_cache_omnifunc=0
"离开插入模式后自动关闭预览窗口
autocmd InsertLeave * if pumvisible() == 0|pclose|endif
"语法关键字补全
let g:ycm_seed_identifiers_with_syntax = 1  
"整合UltiSnips的提示
let g:ycm_use_ultisnips_completer = 1 
"在实现和声明之间跳转,并分屏打开
let g:ycm_goto_buffer_command = 'horizontal-split'
nnoremap <Leader>g :YcmCompleter GoTo<CR>
"与syntastic有冲突，建议关闭
let g:ycm_show_diagnostics_ui = 0
"let g:ycm_error_symbol = '>>'
"let g:ycm_warning_symbol = '>>'
let g:ycm_enable_diagnostic_signs = 0
let g:ycm_enable_diagnostic_highlighting = 0
let g:ycm_echo_current_diagnostic = 0

" WinManager
let g:winManagerWindowLayout='FileExplorer|TagList'
let g:AutoOpenWinManager = 1
nmap wm :WMToggle <CR>

" Airline
set t_Co=256
set laststatus=2
set lazyredraw
let g:airline_theme="molokai"
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#buffer_nr_show = 1
let g:airline#extensions#whitespace#enabled=0   " 关闭空白符检测
let g:airline_powerline_fonts=1 " 使用powerline打过补丁的字体
if !exists('g:airline_symbols')
    let g:airline_symbols={}
endif

" auto-format
"   F7自动格式化代码并保存
noremap <C-s> :Autoformat<CR>:w<CR>
noremap <F7> :Autoformat<CR>
"au BufWrite *.py :Autoformat
"au BufWrite *.c :Autoformat
"au BufWrite *.cpp :Autoformat
let g:autoformat_verbosemode=1
let g:formatdef_google = '"clang-format  -assume-filename=/home/shiyanlou -style=file"'
let g:formatters_c = ['google']
let g:formatters_cpp = ['google']
let g:formatter_yapf_style = 'pep8'

" Indentline
nmap de :IndentLinesToggle <CR>
let g:indentLine_char='┆'
let g:indentLine_enabled = 1

" Ctrlp
let g:ctrlp_cmd = 'CtrlP'
"<Leader>f搜索MRU文件
nmap <Leader>f :CtrlPMRUFiles<CR>
"<Leader>b显示缓冲区文件，并可通过序号进行跳转
nmap <Leader>b :CtrlPBuffer<CR>
"设置搜索时忽略的文件
let g:ctrlp_custom_ignore = {
    \ 'dir':  '\v[\/]\.(git|hg|svn|rvm)$',
    \ 'file': '\v\.(exe|so|dll|zip|tar|tar.gz|pyc)$',
    \ }
let g:ctrlp_working_path_mode = 0
let g:ctrlp_match_window_bottom = 1
"修改QuickFix窗口显示的最大条目数
let g:ctrlp_max_height = 15
let g:ctrlp_match_window_reversed = 0
"设置MRU最大条目数为500
let g:ctrlp_mruf_max = 500
let g:ctrlp_follow_symlinks = 1
"默认使用全路径搜索，置1后按文件名搜索，准确率会有所提高，可以用<C-d>进行切换
let g:ctrlp_by_filename = 1
"默认不使用正则表达式，置1改为默认使用正则表达式，可以用<C-r>进行切换
let g:ctrlp_regexp = 0
"自定义搜索列表的提示符
let g:ctrlp_line_prefix = '♪ '

" auto run
map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
    exec "w"
    if &filetype == 'c'
        exec "!g++ % -o %<"
        exec "!time ./%<"
    elseif &filetype == 'cpp'
        exec "!g++ % -o %<"
        exec "!time ./%<"
    elseif &filetype == 'java'
        exec "!javac %"
        exec "!time java %<"
    elseif &filetype == 'sh'
        :!time bash %
    elseif &filetype == 'python'
        exec "!time python %"
"        exec "!time python3.6 %"
    elseif &filetype == 'html'
        exec "!firefox % &"
    elseif &filetype == 'go'
        exec "!go build %<"
        exec "!time go run %"
    elseif &filetype == 'mkd'
        exec "!~/.vim/markdown.pl % > %.html &"
        exec "!firefox %.html &"
    endif
endfunc

" 其他
colorscheme monokai "设置主题为monokai
" 设置字符编码                                                                
set encoding=utf-8
set termencoding=utf-8
set fileencoding=utf-8
set fileencodings=ucs-bom,utf-8,chinese,cp936
" 语法高亮                                                         
syntax on                                                          
" 检测文件类型                                                     
filetype on                                                        
" 根据文件类型加载对应的插件                                       
filetype plugin on                                                 
" 显示行号                                                      
set number                                                      
" 在第64列显示竖线                                                      
" set cc=64                                                          
" 高亮显示当前行                                                   
set cursorline                                                     
" 设置各种缩进                                                     
set tabstop=4                                                      
set softtabstop=4                                                  
set shiftwidth=4                                                   
set autoindent                                                     
set smartindent                                                    
set cindent                                                        
set hlsearch
"Code fold
set foldmethod=indent
set foldlevelstart=99
" tab转换为空格                                                    
set expandtab
" 将ESC键映射为两次k键 
"inoremap kk <Esc> 

" 按F2或F3在打开的文件之间切换
nnoremap <F2> :bn<CR>
nnoremap <F3> :bp<CR>
nmap wc :bd <CR>    "关闭当前标签
