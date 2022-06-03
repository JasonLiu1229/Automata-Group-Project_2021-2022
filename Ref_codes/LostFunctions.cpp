Player* Maze::getPlayer() {
    return player;
}
Collectable_DFA* Maze::getDFAkeys() {
    return collectedKeys;
}

bool Maze::checkmaze(Path* richting){
    if(richting->isEnemy()){
        return true;
    }
    return false;
}
// algorithms

void Maze::EnemyMovement() {
    for (auto enemy: enemies) {
        movement move = enemy->moveSmartV2();
        if (move == UP and !enemy->GetCurrentTile()->getUp()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getUp());
            enemy->getCurrentTile()->setEnemy(true);
        }else if (move == DOWN and !enemy->GetCurrentTile()->getDown()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getDown());
            enemy->getCurrentTile()->setEnemy(true);
        } else if (move == RIGHT and !enemy->GetCurrentTile()->getRight()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getRight());
            enemy->getCurrentTile()->setEnemy(true);
        } else if (move == LEFT and !enemy->GetCurrentTile()->getLeft()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getLeft());
            enemy->getCurrentTile()->setEnemy(true);
        }
        if(enemy->getCurrentTile() == player->GetCurrentTile()){
            player->playerdied();
        }
    }
}