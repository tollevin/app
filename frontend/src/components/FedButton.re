let component = ReasonReact.statelessComponent("FedButton");

let css = Css.css;
let tw = Css.tw;

let dietButtonClass = [%bs.raw {| css(tw`
  bg-green-darker
  hover:bg-green-darkest
  text-white
  py-1
  px-4
  rounded-lg
  text-lg
`)|}];

let make = (~text : string, _children) => {
  ...component,
  render: _self =>
   <button className=dietButtonClass>
     {ReasonReact.string(text)}
   </button>
};