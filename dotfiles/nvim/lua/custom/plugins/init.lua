-- You can add your own plugins here or in other files in this directory!
--  I promise not to create any merge conflicts in this directory :)
--
-- See the kickstart.nvim README for more information
return {
  -- Alpha (Dashboard)
  -- Added this plugin to initial configuration
  {
    "goolord/alpha-nvim",
    "lervag/vimtex",
    'numToStr/Comment.nvim',
    opts = {
      -- add any options here
    },
    lazy = false,
    "shortcuts/no-neck-pain.nvim"
  },
}
