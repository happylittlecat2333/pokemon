# Server

## Recieve

- sign_up
  - NAME_EXIST
  - SIGN_UP_SUCCESS win lose {pokemon_name attr}     (sendPokemon)
- sign_in
  - USER_NONE
  - PWD_ERROR
  - SIGN_IN_SUCCESS win lose pokemon_num {pokemon_name attr}
- sign_out
- all_user
  - {user_name win lose pokemon_num {pokemon_name attr}}  (sendAllUser)
- online_user
  - {user_name win lose pokemon_num {pokemon_name attr}}  (sendOnlineUser)
- virtual_pkm
  - {pokemon_name attr} (sendPokmeon("admin"))
- pkm_data

## Send

all first: log_type, username

- SIGN_IN: password port
- SIGN_UP: password port
- SIGN_OUT: port
- ALL_USER: port
- ONLINE_USER: port
- VIRTUAL_PKM: port
- PKM_DATA: port username win lose {pokemon_name attr}
  
## QUESTION

- login中的数据，是在什么时候传到mainwindows中，不是已经delete了吗？