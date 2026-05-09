#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void EnsureConfigExists(const fs::path& nook_dir) {
  fs::path config_dir = nook_dir / "config";
  fs::path vimrc_path = config_dir / "vimrc";
  
  if (fs::exists(vimrc_path)) return;
  
  fs::create_directories(config_dir);
  
  std::ofstream f(vimrc_path);
  if (!f) return;  // failed to open for writing
  
  f << R"(" --- nook vimrc: minimal config for entry writing ---

" no plugins, no compatibility-mode quirks
set nocompatible
filetype off
syntax off

" enable true color so RGB values render exactly
set termguicolors

" --- color highlights ---

" backgrounds and main text
highlight Normal       guibg=#1c1612 guifg=#e1d7c3 ctermbg=NONE ctermfg=NONE
highlight NonText      guibg=#1c1612 guifg=#1c1612
highlight EndOfBuffer  guibg=#1c1612 guifg=#1c1612

" cursor line (subtle warm tint)
highlight CursorLine   guibg=#241c16
highlight CursorLineNr guifg=#dcaa6e guibg=#241c16
highlight LineNr       guifg=#8c7d65 guibg=#1c1612

" cursor itself
highlight Cursor       guibg=#dcaa6e guifg=#1c1612

" sign column and fold column used as left padding
highlight SignColumn   guibg=#1c1612
highlight FoldColumn   guibg=#1c1612 guifg=#1c1612

" tabline (header)
highlight TabLineFill  guibg=#1c1612 guifg=#1c1612
highlight TabLine      guibg=#1c1612 guifg=#dcaa6e gui=bold
highlight TabLineSel   guibg=#1c1612 guifg=#dcaa6e gui=bold

" winbar (second header row for breathing space)
highlight WinBar       guibg=#1c1612 guifg=#1c1612
highlight WinBarNC     guibg=#1c1612 guifg=#1c1612

" visual selection
highlight Visual guibg=#dcaa6e guifg=#1c1612 gui=NONE

" search
highlight Search       guifg=#1c1612 guibg=#dcaa6e
highlight IncSearch    guifg=#1c1612 guibg=#dcaa6e

" matched parens
highlight MatchParen   guifg=#dcaa6e guibg=#241c16

" --- editor behavior ---

" comfortable text editing for prose and code
set wrap
set linebreak
set breakindent
set nolist

" minimal chrome
set nonumber
set norelativenumber
set noruler
set noshowmode
set noshowcmd
set shortmess+=IF

" replace tildes on empty lines with spaces
set fillchars=eob:\ 

" left padding via sign column and fold column
set signcolumn=yes
set foldcolumn=4

" vertical breathing room
set scrolloff=4

" no swap clutter for short entries
set noswapfile
set nobackup
set nowritebackup

" sensible spacing
set expandtab
set tabstop=4
set softtabstop=4
set shiftwidth=4
set autoindent

" hide statusline (was misbehaving)
set laststatus=0

" --- header (tabline + winbar for two rows of space) ---

set showtabline=2
set tabline=%#TabLineFill#%=%#TabLine#\ %{strftime(\"%a\ %b\ %d\")}\ %#TabLineFill#%=

" --- cursor shape changes by mode ---

let &t_SI = "\<Esc>[6 q"
let &t_EI = "\<Esc>[2 q"
let &t_SR = "\<Esc>[4 q"

" responsive mode switching
set ttimeoutlen=10

" --- behavior on open ---

autocmd VimEnter * redraw!
autocmd BufReadPost * normal! G$
autocmd BufNewFile  * normal! G$
autocmd BufNewFile  * startinsert
  )";

}
