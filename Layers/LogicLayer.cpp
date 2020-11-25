namespace Logic {

    bool initialize = false;

    bool isInitialize() {
        return initialize;
    }


    void initLogicLayer() {
        if (initialize)
            return;
        //todo
        initialize = true;
    }
}