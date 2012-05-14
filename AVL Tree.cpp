#include <cstdlib>
#include <iostream>
using namespace std;

template <class T>
class Fila;

template <class T>
class Elemento;

template <class T>
class Fila{
    protected:
       int tam;
		Elemento<T> *inicio;
    	Elemento<T> *fim;
    public:
       	Fila(){ tam = 0; inicio = fim = NULL; }
		~Fila(){
			Elemento<T> *ptr, *aux;
			for(ptr = inicio; ptr != NULL; ptr = ptr->prox){
				aux = ptr;
			    delete aux;
			}
		};
       	void Insere(T d);
		//void Imprime();
		bool Vazio(){ return (tam == 0); };
       	T Retira();
};

template <class T>
class Elemento{
	public:
      	friend class Fila<T>;
	private:
		T dado;
      	Elemento *prox;
      	Elemento(T d){ dado = d; prox = NULL; };
};

template <class T>
void Fila<T>::Insere(T d){
    if(inicio == NULL){
    	inicio = new Elemento<T>(d);
        this->fim = inicio;
    }
	else{
     	fim->prox = new Elemento<T>(d);
     	fim = fim->prox;
    }
	this->tam++;
    
	cout << tam;
};

template <class T>
T Fila<T>::Retira(){
    if(inicio == NULL) return -1;
 	else{
		Elemento<T> *ptr;
		ptr = inicio;
        inicio=inicio->prox;
        T aux;
        aux = ptr->dado;
        delete ptr;
        this->tam--;
        return aux;
     }
};

template <class T>
class Node;
template <class T>
class Tree;

template <class T>
class Node{
	public:
	 	friend class Tree<T>;
	
	private:
  		T data;
   		Node<T> *right;     
    	Node<T> *left;
    	Node<T> *prev;
		int fb;
    	Node(T d){
    		right = left = prev = NULL;
        	data = d;
			fb = 0;
		}
    	Node(T d, Node<T> *ant){
    		right = left = NULL;
        	prev = ant;
        	data = d;
			fb = 0;
		}
};

template <class T>
class Tree{
	private:
		Node<T> *root;
    	void DeleteTree(Node<T> *rt);
    	void DeleteTree(Tree<T> *tr);

  	public:
      	Tree(){ root = NULL; }
      	Tree(Node<T> *r){ root = r; }
      	~Tree(){ DeleteTree(root); }
      	Node<T> *Root(){ return root; }
		bool Empty(){ return root == NULL; }
		bool Insert(T d);
		bool Remove(T d);
		void TraversePreOrder(Node<T> *R);
      	void TraversePosOrder(Node<T> *R);
      	void TraverseInOrder(Node<T> *R);
      	void TraverseLevelOrder();

		int TreeHeight(Node<T> *node);
		void CalcCheckFB(Node<T> *node);
		void RotateLeft(Node<T> *node);
		void RotateRight(Node<T> *node);
};

template <class T>
void Tree<T>::DeleteTree(Node<T> *rt){
 	if(rt != NULL){ 
    	Node<T> *rgt = rt->left;
        Node<T> *lft = rt->right;
        delete rt;
        DeleteTree(rgt);
        DeleteTree(lft);
     }
};

template <class T>
void Tree<T>::DeleteTree(Tree<T> *tr){
    if(tr->root != NULL){
     	Tree<T> Rgt(tr->root->left);
        Tree<T> Lft(tr->root->right);
        delete tr->root;
        DeleteTree(&Rgt);
        DeleteTree(&Lft);
 	}
};

template <class T>
bool Tree<T>::Insert(T d){
  	if(Empty()){ 
		root = new Node<T>(d);
     	return true;
   	}   
   	else{
     	Node<T> *ptr = root;
     	bool fim = false;
     	while(!fim){
        	if(ptr->data == d) fim = true;
          	else{
				if(d < ptr->data){
					if(ptr->left == NULL){
						ptr->left = new Node<T>(d, ptr);
						CalcCheckFB(ptr);
                    	fim = true;
             		}
                	else ptr = ptr->left;
       			}
              	else{
                	if(ptr->right == NULL){
						ptr->right = new Node<T>(d, ptr);
						CalcCheckFB(ptr);
                      	fim = true;
                   	}
                   else ptr = ptr->right;
              	}
			}
		}  
     	return (ptr->data == d);
   	}
};

template <class T>
void Tree<T>::CalcCheckFB(Node<T> *R){
	Node<T> *aux = R;
	do{	
		R->fb = TreeHeight(R->right) - TreeHeight(R->left);

		if(R->fb == 2 && aux->fb == 1){ 
			RotateLeft(R); 
			CalcCheckFB(R);
		}
		if(R->fb == 2 && aux->fb == -1){ 
			RotateRight(aux); 
			CalcCheckFB(aux); 
			RotateLeft(R); 
			CalcCheckFB(R);
		}	
		if(R->fb == -2 && aux->fb == 1){ 
			RotateLeft(aux); 
			CalcCheckFB(aux); 
			RotateRight(R); 
			CalcCheckFB(R); 
		}	
		if(R->fb == -2 && aux->fb == -1){ 
			RotateRight(R); 
		 	CalcCheckFB(R); 
		 }
		
		aux = R;
		R = R->prev;		
	}while(R != NULL);
}

template <class T>
void Tree<T>::RotateLeft(Node<T> *aux){
	Node<T> *q, *temp, *ant;
	ant = aux->prev;

	q = aux->right;
	temp = q->left;
	//temp->prev = aux;
	q->left = aux;
	aux->right = temp;

	if(aux != root){
		q->prev = ant;
		aux->prev = q;
		if(ant->left == aux) ant->left = q;
		else ant->right = q;
		root = ant;
	}
	else{
		q->prev = NULL;
		aux->prev = q;
		root = q;
	} 
}
	
template <class T>
void Tree<T>::RotateRight(Node<T> *aux){ 
	Node<T> *q, *temp, *ant;
	ant = aux->prev;
	
	q = aux->left;
	temp = q->right;
	q->right = aux;
	aux->left = temp;
	
	if(aux != root){
		q->prev = ant;
		aux->prev = q;
		if(ant->left == aux) ant->left = q;
		else ant->right = q;
		root = ant;
	}
	else{
		q->prev = NULL;
		aux->prev = q;
		root = q;
	} 
}

template <class T>
int Tree<T>::TreeHeight(Node<T> *node){
    int esq, dir;
    if(node == NULL) return -1;
    esq = TreeHeight( node->left );
    dir = TreeHeight( node->right );
    if(esq > dir) return esq + 1;
    else return dir + 1;
}

template <class T>
bool Tree<T>::Remove(T d){
	Node<T> *ptr = root;
    while(ptr != NULL && ptr->data != d){
    	if(d < ptr->data) ptr = ptr->left;
        else ptr = ptr->right;
    }

    if(ptr == NULL) return false;
    else{
		if(ptr->left == NULL && ptr->right == NULL){
    		if(ptr->prev->left==ptr) ptr->prev->left = NULL;
         	else ptr->prev->right = NULL;
			delete ptr;
			CalcCheckFB(ptr->prev);
     	}
     	else{
			if(ptr->left == NULL || ptr->right == NULL){
          		if(ptr->right == NULL){
             		if(ptr->prev->left == ptr) ptr->prev->left = ptr->left;
             		else ptr->prev->right=ptr->left;
             		delete ptr;
					CalcCheckFB(ptr->prev);
          		}
          		if(ptr->left == NULL){
             		if(ptr->prev->left == ptr) ptr->prev->left = ptr->right;
             		else ptr->prev->right = ptr->right;
             		delete ptr;
					CalcCheckFB(ptr->prev);
          		}
     		}
     		else{
         		Node<T> *sub = ptr->right;
				while(sub->left != NULL) sub = sub->left;
         		sub->prev->left = sub->right;
         		sub->right->prev = sub->prev;
         		ptr->data = sub->data;
         		delete sub;
				CalcCheckFB(ptr);
     		}
		}
	}
    return true;
};

template <class T>
void Tree<T>::TraversePreOrder(Node<T> *R){
 	if(R != NULL){   
		cout << R->data;
		if(R->left != NULL){ 
			cout << ",";
			TraversePreOrder(R->left);
		}
		if(R->right != NULL){
			cout << ",";
        	TraversePreOrder(R->right);
		}
    }
};

template <class T>
void Tree<T>::TraversePosOrder(Node<T> *R){
	if(R->left != NULL){
		TraversePosOrder(R->left);
		cout << ",";
	}
	if(R->right != NULL){
		TraversePosOrder(R->right);
		cout << ",";
	}
	cout << R->data;
};

template <class T>
void Tree<T>::TraverseInOrder(Node<T> *R){
	if(R->left != NULL){
		TraverseInOrder(R->left);
		cout << ",";
	}
	cout << R->data;
	if(R->right != NULL){
		cout << ",";
		TraverseInOrder(R->right);
	}
};

template <class T>
void Tree<T>::TraverseLevelOrder(){
	// Fila< Node<T> > Queue;
	// Node<T> *ptr;
	
	// Queue.Insere(root);
	// ptr = Queue.Retira();
	// while(!Queue.Vazio()){
	// 		Node<T> *tes = Queue.Retira();
	// 		cout << tes->data;
	// 		if(ptr->right != NULL){ Queue.Insere(ptr->right); }
	// 		if(ptr->left != NULL){ Queue.Insere(ptr->left); }
	// 	}
	
};

int main(int argc, char *argv[]){
    Tree<int> Apple;

    Apple.Insert(8);
	Apple.Insert(10);
	Apple.Insert(4);
	Apple.Insert(2);
	Apple.Insert(6);
	Apple.Insert(5);
	
	// Apple.Remove(5);
	// Apple.Remove(4);

    
    cout << "PRE-ORDER:" << endl;
    Apple.TraversePreOrder(Apple.Root());
	cout << endl << endl;
	
	cout << "POS-ORDER:" << endl;
	Apple.TraversePosOrder(Apple.Root());
	cout << endl << endl;
		
	cout << "IN-ORDER:" << endl;
	Apple.TraverseInOrder(Apple.Root());
	cout << endl << endl;
	
	cout << "LEVEL-ORDER:" << endl;
	Apple.TraverseLevelOrder();
	cout << endl << endl;
	
    return 0;
}
