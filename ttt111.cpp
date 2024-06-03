friend difference_type operator-(const list_iterator &end,
                                 const list_iterator &begin) {
    difference_type n =0 ;
    for (; copy!=end; ++n, ++begin){}
    return n;
}