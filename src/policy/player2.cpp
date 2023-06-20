#include <cstdlib>
#include <unordered_map>
#include <iostream>
using namespace std;
#include "../state/state.hpp"
#include "./player2.hpp"
//typedef  pair < State , int >  prr;
int value;
std::unordered_map<std::string,int> transtable;

int player2::alphabeta(State *state,int depth,int alpha,int beta,bool me){
  state->get_legal_actions();
  if(transtable.count(state->encode_state()))return transtable[state->encode_state()];
  if(depth==0||state->legal_actions.empty()){
    std::string key = state->encode_state();
    transtable.insert({key,value});
    return (me?state->evaluate():state->evaluate()*-1);
  }
  if(me){
    
    value=-1e6;
    for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
      value=std::max(value,alphabeta(state->next_state(*actions),depth-1,alpha,beta,!me));
      alpha=std::max(value,alpha);
      if(alpha>=beta)break;
    }
    std::string key = state->encode_state();
    transtable.insert({key,value});
    return value;
  }
  else {
    value=1e6;
    for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
      value=std::min(value,alphabeta(state->next_state(*actions),depth-1,alpha,beta,!me));
      beta=std::min(value,beta);
      if(alpha>=beta)break;
    }
    std::string key = state->encode_state();
    transtable.insert({key,value});
    return value;
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
  

  int lrg=-1e6;
  Move bst;
  for(auto actions = state->legal_actions.begin();actions!=state->legal_actions.end();actions++){
    int result=alphabeta(state->next_state(*actions),depth-1,-1e6,1e6,0);

    if(lrg<result){
      lrg=result;
      bst=*actions;
    }
  }
  return bst;
}