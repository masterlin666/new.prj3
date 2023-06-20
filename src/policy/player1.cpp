#include <cstdlib>

#include "../state/state.hpp"
#include "./player1.hpp"
int val;
int Minimax::minimax(State *state,int depth,bool me){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth==0||state->legal_actions.empty())return state->evaluate();
  if(me){
    val=-999999;
    for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
      val=std::max(val,minimax(state->next_state(*actions),depth-1,!me));
    }
    return val;
  }
  else {
    val=999999;
    for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
      val=std::min(val,minimax(state->next_state(*actions),depth-1,!me));
    }
    return val;
  }

}

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
   
  int lrg=-99999;
  Move bst;
  for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
    
    int result=minimax(state->next_state(*actions),depth-1,0);
    if(lrg<result){
      lrg=result;
      bst=*actions;
    }
  }
  
  /*for(int i=0;i<depth;i++){
    k=rand()/k;
  }*/
  return bst;
}