#include <iostream>

#define ERRORCODE 1
#define EXITCODE 0

using namespace std;

class Matrix{
private:
    int Row;
    int Column;
    float **mat;
public:
    Matrix();
    Matrix(int,int);
    ~Matrix();
    void resetMatrix(int, int);
    void clear();

    int getRow() const;
    int getColumn() const;
    float** getAddress();
    float getUnit(int,int);
    void setUnit(int,int,float);
    void print();
};

Matrix::Matrix(){
    Row=Column=0;
    *mat = nullptr;
    mat = nullptr;
}
Matrix::Matrix(int row,int column){
    Row=row,Column=column;
    mat=new float*[Row];
    for(int i=0;i<Row;i++){
        mat[i]=new float[Column];
    }

    if(mat==nullptr){
        cout<<"insufficient memory";
        exit(ERRORCODE);
    }

    for(int i=0;i<Row;i++){
        for(int j=0;j<Column;j++){
            if(Row==Column&&i==j){
                mat[i][j]=1;
            }else mat[i][j]=0;
        }
    }
}
void Matrix::resetMatrix(int row, int column){
    for(int i=0;i<Row;i++){
        delete []mat[i];
    }
    delete []mat;
	Row=row,Column=column;
    mat=new float*[Row];
    for(int i=0;i<Row;i++){
        mat[i]=new float[Column];
    }

    for(int i=0;i<Row;i++) {
        for (int j = 0; j < Column; j++) {
            if (Row == Column && i == j) {
                mat[i][j] = 1;
            } else mat[i][j] = 0.0;
        }
    }

    if(mat==nullptr){
        cout<<"insufficient memory";
        exit(ERRORCODE);
    }
}
Matrix::~Matrix(){
	for(int i=0;i<Row;i++){
    	delete []mat[i];
	}
	delete []mat;
}
void Matrix::clear(){
    for(int i=0;i<Row;i++) {
        for (int j = 0; j < Column; j++) {
            mat[i][j] = 0.0;
        }
    }
}
int Matrix::getRow() const{
    return Row;
}
int Matrix::getColumn() const{
    return Column;
}
float** Matrix::getAddress(){
	return mat;
}
float Matrix::getUnit(int Row,int Column){
    return mat[Row][Column];
}
void Matrix::setUnit(int Row,int Column,float data){
    mat[Row][Column]=data;
}
void Matrix::print(){
    for(int i=0;i<Row;i++){
        for(int j=0;j<Column;j++){
            printf("%7.1f",mat[i][j]);
        }
        cout<<endl;
    }
    cout<<endl;
}