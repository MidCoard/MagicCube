namespace Logic {

    bool initialize = false;

    bool isInitialize() {
        return initialize;
    }

    void updateGameState() {

    }

    void initLogicLayer() {
        if (initialize)
            return;
        initialize = true;
    }
}