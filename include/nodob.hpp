
template <typename Key>
class NodoB {
  protected: 
    Key dato_;
    NodoB<Key> *izdo_;
    NodoB<Key> *dcho_;

  public:
    NodoB(const Key k) : dato_(k), izdo_(nullptr), dcho_(nullptr) {}
    const Key& getDato() const {return dato_;}
};