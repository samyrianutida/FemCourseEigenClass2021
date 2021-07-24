/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeomQuad.h"

GeomQuad::GeomQuad() {
}

GeomQuad::~GeomQuad() {
}

GeomQuad::GeomQuad(const GeomQuad& copy) {
    fNodeIndices = copy.fNodeIndices;
}

GeomQuad& GeomQuad::operator=(const GeomQuad& copy) {
    fNodeIndices = copy.fNodeIndices;
    return *this;
}

void GeomQuad::Shape(const VecDouble& xi, VecDouble& phi, MatrixDouble& dphi) {
    if (xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) { DebugStop(); };
    // Implement stars at this point

    double qsi = xi[0];
    double eta = xi[1];

    phi.resize(4);
    dphi.resize(2, 4);

    phi(0) = (1. / 4.) * (1. - qsi) * (1. - eta);
    phi(1) = (1. / 4.) * (1. + qsi) * (1. - eta);
    phi(2) = (1. / 4.) * (1. + qsi) * (1. + eta);
    phi(3) = (1. / 4.) * (1. - qsi) * (1. + eta);

    dphi(0, 0) = (1. / 4.) * (-1 + eta);
    dphi(1, 0) = (1. / 4.) * (-1 + qsi);

    dphi(0, 1) = (1. - eta) / 4.;
    dphi(1, 1) = (1. / 4.) * (-1 - qsi);

    dphi(0, 2) = (1. + eta) / 4.;
    dphi(1, 2) = (1. + qsi) / 4.;

    dphi(0, 3) = (1. / 4.) * (-1 - eta);
    dphi(1, 3) = (1. - qsi) / 4.;

}
//end

void GeomQuad::X(const VecDouble& xi, MatrixDouble& NodeCo, VecDouble& x) {
    if (xi.size() != Dimension) DebugStop();
    if (x.size() < NodeCo.rows()) DebugStop();
    if (NodeCo.cols() != nCorners) DebugStop();

    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    if (x.size() < nrow) {
        x.resize(2);
    }

    x.setZero();

    VecDouble phi(nCorners);
    MatrixDouble dphi(Dimension, nCorners);


    Shape(xi, phi, dphi);
    int space = NodeCo.rows();

    for (int i = 0; i < space; i++) {
        x[i] = 0.0;
        for (int j = 0; j < nCorners; j++) {
            x[i] += phi[j] * NodeCo(i, j);
        }
    }

}

void GeomQuad::GradX(const VecDouble& xi, MatrixDouble& NodeCo, VecDouble& x, MatrixDouble& gradx) {


    if (xi.size() != Dimension) DebugStop();
    if (x.size() != NodeCo.rows()) DebugStop();
    if (NodeCo.cols() != nCorners) DebugStop();

    gradx.resize(2, 2);
    gradx.setZero();

    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    if (x.size() < nrow) {
        x.resize(2);
    }
    x.setZero();

    VecDouble phi(nCorners);
    MatrixDouble dphi(Dimension, nCorners);

    Shape(xi, phi, dphi);
    int space = NodeCo.rows();

    for (int i = 0; i < nCorners; i++) {
        for (int j = 0; j < Dimension; j++) {
            x[j] += NodeCo(j, i) * phi[i];
            gradx(j, 0) += NodeCo(j, i) * dphi(0, i);
            gradx(j, 1) += NodeCo(j, i) * dphi(1, i);
        }
    }

}

void GeomQuad::SetNodes(const VecInt& nodes) {
    if (nodes.size() != nCorners) DebugStop();
    fNodeIndices = nodes;
}

void GeomQuad::GetNodes(VecInt& nodes) const {
    nodes = fNodeIndices;
}

int GeomQuad::NodeIndex(int node) const {
    return fNodeIndices[node];
}

int GeomQuad::NumNodes() {
    return nCorners;
}

GeoElementSide GeomQuad::Neighbour(int side) const {
    return fNeighbours[side];
}

void GeomQuad::SetNeighbour(int side, const GeoElementSide& neighbour) {
    fNeighbours[side] = neighbour;
}