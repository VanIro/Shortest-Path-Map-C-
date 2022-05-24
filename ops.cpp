#include <iostream>
#include "khojiRukh.cpp"

bool operator<(g_node *gN, struct khojiRukhNode& kB){
    return(gN->elm->getName() < kB.tL->gN->elm->getName());
}
bool operator==(g_node *gN, struct khojiRukhNode& kB){
    return(gN->elm->getName() == kB.tL->gN->elm->getName());
}
bool operator<(string s, struct khojiRukhNode& kB){
    return(s < kB.tL->gN->elm->getName());
}
bool operator==(string s, struct khojiRukhNode& kB){
    return(s == kB.tL->gN->elm->getName());
}
