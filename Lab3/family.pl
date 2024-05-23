female(lucy).
female(amy).
female(kgomotso).
female(naledi).
female(karen).
female(michelle).

male(greg).
male(adam).
male(trent).
male(martin).
male(marcus).
male(gabriel).
male(dave).
male(michael).

parent(trent, greg).
parent(naledi, greg).
parent(trent, adam).
parent(trent, kgomotso).
parent(karen, adam).
parent(karen, kgomotso).
parent(gabriel, marcus).
parent(gabriel, michelle).
parent(gabriel, naledi).
parent(amy, marcus).
parent(amy, michelle).
parent(amy, naledi).
parent(dave, trent).
parent(dave, martin).
parent(lucy, trent).
parent(lucy, martin).
parent(martin, michael).

married(amy, gabriel).
married(lucy, dave).
married(naledi, trent).

spouse(X,Y) :- married(X,Y).
mother(X,Y) :- parent(X,Y), female(X).
father(X,Y) :- parent(X,Y), male(X).
sibling(X, Y) :- mother(Mother, X), mother(Mother, Y), father(Father, X),father(Father, Y), X\=Y.
brother(X, Y) :- male(X), sibling(X, Y).
sister(X, Y) :- female(X), sibling(X, Y).
half_sibling(X, Y) :-
    (
        mother(Mother, X),
        mother(Mother, Y),
        \+
        (
            father(Father, X),
            father(Father, Y)
        )
    );
    (
        father(Father, X),
        father(Father, Y),
        \+
        (
            mother(Mother,X),
            mother(Mother, Y)
        )
    ),
    X\=Y.
half_brother(X, Y) :- half_sibling(X, Y), male(X).
half_sister(X, Y) :- half_sibling(X, Y), female(X).
uncle(X, Y) :- parent(Z, Y), brother(X, Z).
aunt(X, Y) :- parent(Z, Y), sister(X, Z).
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandmother(X, Y) :- grandparent(X, Y), female(X).
grandfather(X, Y) :- grandparent(X, Y), male(X).
nephew(X, Y) :- parent(Z, X), sibling(Z, Y), male(X).
niece(X, Y) :- parent(Z, X), sibling(Z, Y), female(X).
cousin(X, Y) :- parent(Z, X), parent(W, Y), sibling(Z, W), X \= Y.
in_law(X, Y) :-
    (married(Y,Z), sibling(X,Z)); (married(Z,Y), sibling(X,Z)).

brother_in_law(X, Y) :- (in_law(X, Y); in_law(Y, X)), male(X).
sister_in_law(X, Y) :- (in_law(X, Y); in_law(Y, X)), female(X).
