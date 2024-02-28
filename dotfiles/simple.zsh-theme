#colors are sourced(blue,white etc.) from the terminal st in the config.h file in the array
PROMPT='%B%n%F{blue} %f%M %F{white}%~%f%b%B$(git_prompt_info)%b  '
#PROMPT='%F{blue} %f%B%n@%M %~%b%B$(git_prompt_info)%b  '

ZSH_THEME_GIT_PROMPT_PREFIX=" %{%}("
ZSH_THEME_GIT_PROMPT_SUFFIX="%{%})"
ZSH_THEME_GIT_PROMPT_CLEAN=" %{%}"
ZSH_THEME_GIT_PROMPT_DIRTY=" %{%}󰊢"
