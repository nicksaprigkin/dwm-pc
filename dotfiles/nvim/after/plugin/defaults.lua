-- SETS
vim.opt.nu = true
vim.opt.relativenumber = true

vim.opt.tabstop = 4
vim.opt.softtabstop = 4
vim.opt.shiftwidth = 4
vim.opt.expandtab = true

vim.opt.smartindent = true

vim.opt.ttyfast = true --speed up scrolling in Vim

vim.opt.swapfile = false
vim.opt.backup = false
vim.opt.undodir = os.getenv("HOME") .. "/.vim/undodir"
vim.opt.undofile = true

vim.opt.hlsearch = false
vim.opt.incsearch = true

vim.opt.scrolloff = 8
vim.opt.isfname:append("@-@")

vim.opt.updatetime = 50

-- signcolumn removed and colorcolumn added
vim.opt.colorcolumn = "80"
vim.cmd('set signcolumn=no')

-- tab bar at the top, 2 = always show, 1 = show when more than one tab, 0 = never show
vim.cmd('set showtabline=2')
vim.cmd('highlight TabLineSel guifg=White')

-- make the background transparent while having a theme
vim.cmd('highlight LineNr ctermbg=NONE guibg=NONE')
vim.cmd('highlight CursorLineNr ctermbg=NONE guibg=NONE')
vim.cmd('highlight Normal ctermbg=NONE guibg=NONE')
-- vim.cmd('highlight ColorColumn ctermbg=0 guibg=0 guifg=NONE ctermfg=NONE')

--REMAPS
vim.g.mapleader = " "
vim.keymap.set("n", "<leader>pv", vim.cmd.Ex)

vim.keymap.set("v", "J", ":m '>+1<CR>gv=gv")
vim.keymap.set("v", "K", ":m '<-2<CR>gv=gv")

vim.keymap.set("n", "J", "mzJ`z")
vim.keymap.set("n", "<C-d>", "<C-d>zz")
vim.keymap.set("n", "<C-u>", "<C-u>zz")
vim.keymap.set("n", "n", "nzzzv")
vim.keymap.set("n", "N", "Nzzzv")

-- greatest remap ever
vim.keymap.set("x", "<leader>p", [["_dP]])

-- next greatest remap ever : asbjornHaland
vim.keymap.set({ "n", "v" }, "<leader>y", [["+y]])
vim.keymap.set("n", "<leader>Y", [["+Y]])

vim.keymap.set({ "n", "v" }, "<leader>d", [["_d]])

vim.keymap.set("n", "Q", "<nop>")
vim.keymap.set("n", "<C-f>", "<cmd>silent !tmux neww tmux-sessionizer<CR>")
vim.keymap.set("n", "<leader>f", vim.lsp.buf.format)

vim.keymap.set("n", "<C-k>", "<cmd>cnext<CR>zz")
vim.keymap.set("n", "<C-j>", "<cmd>cprev<CR>zz")
vim.keymap.set("n", "<leader>k", "<cmd>lnext<CR>zz")
vim.keymap.set("n", "<leader>j", "<cmd>lprev<CR>zz")

vim.keymap.set("n", "<leader>s", [[:%s/\<<C-r><C-w>\>/<C-r><C-w>/gI<Left><Left><Left>]]) --replace
--80char format
vim.keymap.set("n", "<leader>c", [[:%s/.\{80}\($\)\@!/&\r/g]])

vim.keymap.set("n", "<leader>x", "<cmd>!chmod +x %<CR>", { silent = true })

vim.keymap.set("n", "<leader>mr", "<cmd>CellularAutomaton make_it_rain<CR>");

vim.keymap.set("n", "<leader><leader>", function()
    vim.cmd("so")
end)

--open zathura with the correct file
vim.keymap.set("n", "<leader>z", ":silent !zathura %:r.pdf &<CR>", { silent = true })

-- UTF 8 for all languages support
vim.opt.encoding = 'utf-8'

-- line wrapping
vim.opt.wrap = true
