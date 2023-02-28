(lang dune 3.4)
(name mulua)

(generate_opam_files true)

(package
 (name mulua)
 (synopsis "The muLua programming language")
 (depends
  (ocaml (and (>= 4.14) (< 5.0)))

  ; Build
  (ppx_jane (and :build (>= 0.15.0)))
  (ppx_compose (and :build (>= 0.2.1)))
  (ppx_gen_rec (and :build (>= 2.0.0)))
  (menhir (and :build (>= 20220210)))
  (reason (and :build (>= 3.8.0)))

  ; Development
  (bisect_ppx (and :dev (>= 2.8.1)))

  ; Documentation
  (odoc (and :with-doc (>= 2.1.1)))

  ; Runtime
  (core (>= 0.15.0))
  (cmdliner (>= 1.1.1))
  (sedlex (>= 2.5))
  (menhirLib (>= 20220210))))

(using menhir 2.1)
