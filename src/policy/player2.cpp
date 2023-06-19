#include <cstdlib>

#include "../state/state.hpp"
#include "./player2.hpp"
int value;
int player2::alphabeta(State *state,int depth,int alpha,int beta,bool me){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth==0||state->legal_actions.empty())return state->evaluate();
  if(me){
    alpha=-999999;
    for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
      value=std::max(value,alphabeta(state->next_state(*actions),depth-1,alpha,beta,!me));
      if(alpha>=beta)break;
    }
    return alpha;
  }
  else {
    beta=999999;
    for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
      value=std::min(beta,alphabeta(state->next_state(*actions),depth-1,alpha,beta,!me));
      if(alpha>=beta)break;
    }
    return beta;
  }

}

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move player2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
   
  int lrg=-99999;
  Move bst;
  for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
    
    int result=alphabeta(state->next_state(*actions),depth,0,0,0);
    if(result<=0)result=result*(-1);
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