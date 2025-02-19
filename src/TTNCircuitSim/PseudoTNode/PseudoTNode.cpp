#include "PseudoTNode.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include "../../Operations/TTNContract/TTNContract.h"
#include "../../Operations/Walker/Walker.h"

PseudoTNode::PseudoTNode(const std::string& name, const std::vector<int>& shape, std::shared_ptr<PseudoTNode> parent)
    : name_(name), shape_(shape), local_dim_(shape[0]), parent_(parent) {}

void PseudoTNode::addChild(std::shared_ptr<PseudoTNode> child) {
    children_.push_back(child);
}

const std::vector<int>& PseudoTNode::getShape() const {
    return shape_;
}

void PseudoTNode::setShape(const std::vector<int>& new_shape) {
    // Update the shape of the node
    shape_ = new_shape;

    // Update the local dimension based on the new shape
    if (!shape_.empty()) {
        local_dim_ = shape_[0]; // Assuming the first dimension is the local dimension
    } else {
        local_dim_ = 0; // Handle the case where shape might be empty
    }
}

const std::string& PseudoTNode::getName() const {
    return name_;
}

const std::unordered_map<std::string, int>& PseudoTNode::getLeafIndices() const {
    return leaf_indices_;
}

void PseudoTNode::setLeafIndices(const std::unordered_map<std::string, int>& leaf_indices) {
    leaf_indices_ = leaf_indices;
}

bool PseudoTNode::isLeaf() const {
    return children_.empty();
}

bool PseudoTNode::isRoot() const {
    return parent_ == nullptr;
}

void PseudoTNode::display(int depth) const {
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }
    std::cout << name_ << std::endl;
    for (const auto& child : children_) {
        child->display(depth + 1);
    }
}

std::shared_ptr<PseudoTNode> PseudoTNode::getParent() const {
    return parent_;
}

std::vector<std::shared_ptr<PseudoTNode>> PseudoTNode::getChildren() const {
    return children_;
}

void PseudoTNode::applyGate(const Tensor& gate_matrix) {
    assert(isLeaf());
}

void PseudoTNode::applyGateAndReshape(const Tensor& update) {
    assert(isLeaf());
    int gate_dim = update.cols();
    shape_ = {local_dim_, shape_[1] * gate_dim};
}
