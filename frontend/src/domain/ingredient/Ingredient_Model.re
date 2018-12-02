type _data = {
  id: UUID.t,
  name: string,
  /* UI */
};

type _local = unit;
type _record = RecordType.t(_data, _local);

let fragmentType = "Ingredient";
let fragmentName = "ingredientFields";
module ModelSchema = Schema.Ingredient;
type idType = ModelSchema.idAsType(Schema.modelIdType);

let idToTypedId = (id: UUID.t): idType => `IngredientId(id);

module GraphFragment = [%graphql
  {|
    fragment ingredientFields on Ingredient {
      id
      name
    }
  |}
];

module Fragment = {
  include GraphFragment;
  module Fields = GraphFragment.IngredientFields;
};
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

let _defaultData = id => {
  id: id,
  name: "",
  /* UI */
};

let _defaultRecordId = id: _record => {
  data: _defaultData(id),
  local: (),
};

let _defaultRecord = (): _record => _defaultRecordId(UUID.generateUUID());

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;

  module Data = {
    type t = _data;
    let fromObject = (obj: Fragment.Fields.t): t => {
      id: obj##id,
      name: obj##name,
    };
  };

  let default = () => _defaultRecord();
  let defaultWithId = ((), id): t =>
    _defaultRecordId(id |> Schema.getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: (),
  };
};


