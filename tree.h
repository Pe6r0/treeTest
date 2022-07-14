#include <vector>
#include <memory>

namespace kr{
class Tree
{
public:

    Tree()
    {
        
    }

    Tree(int data) : _data{data} 
    {
    
    }

    virtual bool operator==(Tree& other)
    {
        return _data == other._data;
    }

    //add clone copy = == etc

    virtual ~Tree() {};

    std::vector<std::unique_ptr<Tree> >& getChildren() { return _children; }

    virtual void insertElement(int element)
    {
        _children.resize(_children.size() + 1);
        (*_children.rbegin()) = std::make_unique<Tree>(element);
    }

    virtual void removeElement(int element)
    {
        //add
    }

    void setData(int d)
    {
        _data = d;
    }

protected:
    std::vector<std::unique_ptr<Tree> > _children;

    int _data = 0;
};

class BinarySearchTree : public Tree
{
public:
    BinarySearchTree() : Tree() {}

    BinarySearchTree(int data) : Tree(data), _empty{ false }
    {
        Tree::_children.resize(2);
    }

    void insertElement(int element) override
    {
        if (_empty)
        {
            Tree::_data = element;
            _empty = false;
            Tree::_children.resize(2);
            (*_children.begin()) = std::make_unique<BinarySearchTree>();
            (*_children.rbegin()) = std::make_unique<BinarySearchTree>();
            return;
        }

        if (element < Tree::_data)
        {
            auto* left = dynamic_cast<BinarySearchTree*>((*_children.begin()).get());
            if (left != nullptr)
                left->insertElement(element);
        }
        else
        {
            auto* right = dynamic_cast<BinarySearchTree*>((*_children.rbegin()).get());
            if (right != nullptr)
                right->insertElement(element);
        }
    }

    int getHeight()
    {
        if(_empty)
        {
            return 0;
        }
        int leftHeight = 0;
        int rightHeight = 0;
        auto* left = dynamic_cast<BinarySearchTree*>((*_children.begin()).get());
        auto* right = dynamic_cast<BinarySearchTree*>((*_children.rbegin()).get());

        leftHeight = 1 + left->getHeight();
        rightHeight = 1 + right->getHeight();
        return std::max(leftHeight, rightHeight);

    }

    //add clone copy = == etc

    virtual ~BinarySearchTree() {};

protected:
    bool _empty = true;

};

class BinaryBalancedSearchTree : public BinarySearchTree
{
public:
    BinaryBalancedSearchTree() : BinarySearchTree() {}

    BinaryBalancedSearchTree(int data) : BinarySearchTree(data) {}

    void insertElement(int element) override
    {
        BinarySearchTree::insertElement(element);

        if (!isBalanced())
        {

        }
        
    }
    
    //add clone copy = == etc



    bool isBalanced()
    {
        if (_empty)
        {
            return true;
        }
        int leftHeight = 0;
        int rightHeight = 0;
        auto* left = dynamic_cast<BinarySearchTree*>(_children.begin()->get());
        auto* right = dynamic_cast<BinarySearchTree*>(_children.rbegin()->get());
        leftHeight = left->getHeight();
        rightHeight = right->getHeight();
        
        return std::abs(leftHeight - rightHeight) <= 1;
    }
    
    ~BinaryBalancedSearchTree() {};

private:

};


}