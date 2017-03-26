#ifndef MOVEMENTMODEL_H
#define MOVEMENTMODEL_H

class MovementModel {
    protected:
      int *data;

    public:
        MovementModel(int *arr){
            data = arr;
        }

      virtual void execute(float goals[2]){};
};

#endif //MOVEMENTMODEL_H
