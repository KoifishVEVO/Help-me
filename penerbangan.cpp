#include "penerbangan.h"

// Implementasi Fungsi-Fungsi

adr_parent createElmParent(infotype x) {
    adr_parent p = new elmParent();
    p->info = x;
    p->next = NULL;
    p->prev = NULL;
    p->jadwalP = NULL;
    return p;
}

adr_child createElmChild(infoJadwal* x) {  // Perubahan disini
    adr_child P = new elmChild;
    P->info = x;
    P->next = NULL;
    return P;
}

address createRelation() {
    address newRelation = new elmRelation;
    newRelation->next = NULL;
    newRelation->next_child = NULL;
    return newRelation;
}

void insertFirstParent(List_maskapai &L, adr_parent p) {
    if (L.first == NULL) {
        L.first = p;
        L.last = p;
    } else {
        p->next = L.first;
        L.first->prev = p;
        L.first = p;
    }
}

void insertLastParent(List_maskapai &L, adr_parent P) {
    if (L.first == NULL) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

void showParent(List_maskapai L) {
    if (L.first != NULL) {
        adr_parent q = L.first;
        while (q != NULL) {
            cout << "Maskapai ID: " << q->info.id << endl;
            cout << "Maskapai Nama: " << q->info.nama << endl;
            cout << "Maskapai Kapasitas: " << q->info.kapasitas << endl;
            cout << " " << endl;
            q = q->next;
        }
    }
}

void deleteFirst(List_maskapai &L) {
    if (L.first != NULL) {
        adr_parent p = L.first;
        L.first = p->next;
        p->next = NULL;
        L.first->prev = NULL;
        p->jadwalP = NULL;

    }
}


void deleteAfterChild(List_jadwal &L, adr_child P)
{
    adr_child Q = L.first;

    while (Q->next != P){

        Q = Q->next;
    }
    Q->next = P->next;
    P->next = NULL;

}

adr_parent searchParent(List_maskapai L, infotype x) {
    adr_parent p = L.first;

    while (p != NULL) {
        if ((p->info.nama == x.nama && p->info.id == x.id && p->info.kapasitas && x.kapasitas) || p->info.id == x.id) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}



void deleteAfterRelation(List_maskapai &L, adr_parent P, adr_child childAddr) {
    if (P->jadwalP != NULL) {
        address Q = P->jadwalP;
        address J;

          while (Q->next != NULL && Q->next->next_child != childAddr) {
                J = Q;
        // Check if the first relation is the one to be deleted
        if (Q->next_child == childAddr) {
            P->jadwalP = Q->next;
            Q->next = NULL;
            Q->next_child = NULL;
            delete Q;
        } //if last

        else if (Q->next == NULL) {
            delete Q;
            } else {
              J->next = Q->next;
              Q->next = NULL;
              delete Q;
            }


            Q = Q->next;
        }
    }
}


void deleteRelations(List_maskapai &L, infotype x) {
    adr_parent parent = searchParent(L, x);

    if (parent != NULL) {
        address Q = parent->jadwalP;
        address P = Q->next;

        while (P != NULL) {
            Q->next = P->next;
            P->next = NULL;
            P->next_child = NULL;
            P = Q->next;
        }
    }
}

void deleteAfterWithRelation(List_maskapai &L, infotype x) {
    adr_parent P = searchParent(L, x);
    adr_parent Q = P->prev;

    if (P != NULL) {
        //if 1 elemen
        if (P == L.first && P == L.last) {
            L.first = NULL;
            L.last = NULL;

        }
        // di awal
        else if (P == L.first) {
            L.first = P->next;
            L.first->prev = NULL;
            P->next = NULL;

        }
        //di akhir
        else if (P == L.last) {
            L.last = L.last->prev;
            L.last->next = NULL;
            P->prev = NULL;

        }
        //di tengah
        else {
            Q->next = P->next;
            P->next->prev = Q;
            P->next = NULL;
            P->prev = NULL;

        }
        cout << "Data  Maskapai dengan id: " << x.id << " Berhasil Dihapus! "<<endl;
    } else{
        cout << "Data Maskapai dengan id: " << x.id << "Tidak Ditemukan! "<<endl;
    }
}

void showJadwal(List_jadwal L) {
    adr_child p = L.first;
    while (p != NULL) {
        cout << "Rute: " << p->info->rute << ", Jadwal: " << p->info->jadwal
             << ", Status: " << p->info->status << ", Jam: " << p->info->jam << endl;
        p = p->next;
    }
}

int countChildren(List_maskapai &L, infotype x) {
    int count = 0;
    address rel = searchParent(L, x)->jadwalP;

    while (rel != NULL){
        count++;
        rel = rel->next;
    }
    return count;
}

void insertLastChild(List_jadwal &L, adr_child P) {
    adr_child Q = L.first;
    if (L.first == NULL) {
        L.first = P;
    } else {
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void InsertFirstChild(List_jadwal &L, adr_child P) {
    if (L.first == NULL) {
        L.first = P;
    } else {
        P->next = L.first;
        L.first = P;
    }
}

adr_child searchChild(List_jadwal &L, infoJadwal* x) {
    adr_child p = L.first;
    while (p != NULL) {
        if (p->info == x || p->info->rute == x->rute) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void deleteRelationsChild(adr_parent p, address relationToDelete) {
    if (p != NULL && p->jadwalP != NULL && relationToDelete != NULL) {
        if (p->jadwalP == relationToDelete) {
            p->jadwalP = relationToDelete->next;
            relationToDelete->next = NULL;
            cout << "Relation successfully deleted!" << endl;
        } else {
            address prevRelation = p->jadwalP;
            address currentRelation = prevRelation->next;

            while (currentRelation != NULL && currentRelation != relationToDelete) {
                prevRelation = currentRelation;
                currentRelation = currentRelation->next;
            }

            if (currentRelation == relationToDelete) {
                prevRelation->next = currentRelation->next;
                currentRelation->next = NULL;
                delete currentRelation;
                cout << "Relation successfully deleted!" << endl;
            } else {
                cout << "Specified relation not found!" << endl;
            }
        }
    } else {
        cout << "Parent or relations not found!" << endl;
    }
}



void deleteChildWithRelation(List_jadwal &L, infotype parentInfo, infoJadwal childInfo) {
    adr_child child = searchChild(L, childInfo);
    List_jadwal J;
    bool found = false;


    if (parent != NULL) {
        address prevRelation = parent->jadwalP;
        address currentRelation = prevRelation->next;
        address currentRelationFirst = prevRelation;
        deleteAfterChild()

        if (currentRelationFirst->next_child->info->rute == childInfo.rute){
            currentRelationFirst->next = NULL;
            currentRelationFirst->next_child = NULL;
        }

        while (currentRelation != NULL && currentRelation->next_child->info->rute != childInfo.rute) {
            prevRelation = currentRelation;
            currentRelation = currentRelation->next;
        }

        if (currentRelation != NULL && currentRelation->next_child->info->rute == childInfo.rute) {
            adr_child childTarget = currentRelation->next_child;
            prevRelation->next = currentRelation->next;
            currentRelation->next_child = NULL;
            currentRelation->next = NULL;
            delete childTarget;
            cout << "Success" << endl;
        } else {
            cout << "Data Jadwal tidak ditemukan" << endl;
        }
    } else {
        cout << "Data Maskapai tidak ditemukan" << endl;
    }

}



void createRelation(List_maskapai &L, List_jadwal &J, infotype parentInfo, infoJadwal* childInfo) {
    adr_parent parent = searchParent(L, parentInfo);
    adr_child child = searchChild(J, childInfo);

    if (parent != NULL && child != NULL) {
        address newRelation = createRelation();
        newRelation->next_child = child;
        newRelation->next = NULL;

        // Menambahkan relasi baru ke akhir daftar relasi maskapai
        if (parent->jadwalP == NULL) {
            parent->jadwalP = newRelation;
        } else {
            address lastRelation = parent->jadwalP;
            while (lastRelation->next != NULL) {
                lastRelation = lastRelation->next;
            }
            lastRelation->next = newRelation;
        }

        cout << "Relation created successfully!\n";
    } else {
        cout << "Parent or Child not found!\n";
    }
}


void showParentWithChildren(List_maskapai L) {
    adr_parent q = L.first;
    while (q != NULL) {
        cout << "Maskapai ID: " << q->info.id << endl;
        cout << "Maskapai Nama: " << q->info.nama << endl;
        cout << "Maskapai Kapasitas: " << q->info.kapasitas << endl;

        address child = q->jadwalP;
        cout << "Jadwal:\n";
        while (child != NULL) {
            cout << "  - Rute: " << child->next_child->info->rute << ", Jadwal: " << child->next_child->info->jadwal
                 << ", Status: " << child->next_child->info->status << ", Jam: " << child->next_child->info->jam << endl;
            child = child->next;
        }

        q = q->next;
    }
}


void searchChildDalamParent(List_maskapai L, infotype parentInfo, infoJadwal childInfo) {
   adr_parent parent = searchParent(L, parentInfo);
   if (parent != NULL) {
       address relation = parent->jadwalP;
       while (relation != NULL) {
           if (relation->next_child->info->rute == childInfo.rute) {
               cout << "Data ditemukan! "<<endl;
                cout << "Rute: "<< relation->next_child->info->rute <<endl;
               cout << "Jadwal: "<< relation->next_child->info->jadwal <<endl;
               cout << "Jam: "<< relation->next_child->info->jam <<endl;
               cout << "Status: "<< relation->next_child->info->status <<endl;
           }
           relation = relation->next;
       }
   } else {
    cout << "Data Jadwal tidak ditemukan";
   }


}
