open Base;

module type S = {
  [@deriving equal]
  type t;

  type key;
  type value;
  type map;

  let default: t => value;
  let different: t => map;

  let const: value => t;

  let get: (t, key) => value;
  let set: (t, ~key: key, ~data: value) => t;

  let merge:
    (t, t, ~f: (~key: [> | `Key(key) | `Other], value, value) => value) => t;
};

module Make =
       (Key: Comparable.S, Value: Equal.S)

         : (
           S with type key := Key.t with type value := Value.t with
             type map := Map.M(Key).t(Value.t)
       ) => {
  [@deriving equal]
  type t = {
    default: Value.t,
    different: Map.M(Key).t(Value.t),
  };

  let default = ({default, _}) => default;
  let different = ({different, _}) => different;

  let const = default => {default, different: Map.empty((module Key))};

  let get = ({default, different}, key) =>
    key |> Map.find(different) |> Option.value(~default);

  let set = ({default, different}, ~key, ~data) => {
    default,
    different:
      Value.equal(data, default)
        ? Map.remove(different, key) : Map.set(different, ~key, ~data),
  };

  let normalize = ({default, different}) => {
    default,
    different: different |> Map.filter(~f=Value.equal(default) %> (!)),
  };

  let merge = (a, b, ~f) =>
    {
      default: f(~key=`Other, a.default, b.default),
      different:
        Map.merge(a.different, b.different, ~f=(~key) =>
          {
            let key = `Key(key);
            fun
            | `Both(x, y) => f(~key, x, y)
            | `Left(x) => f(~key, x, b.default)
            | `Right(y) => f(~key, a.default, y);
          }
          %> Option.some
        ),
    }
    |> normalize;
};
