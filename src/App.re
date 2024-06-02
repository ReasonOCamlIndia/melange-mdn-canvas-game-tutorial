open Webapi;
let canvas = switch(Webapi.Dom.document |> Webapi.Dom.Document.getElementById("canvas")) {
    | Some(canvas) => canvas
    | None => Js.Exn.raiseError("Failed to find canvas")
};
let x = (canvas |> Canvas.CanvasElement.width |> float_of_int) /. 2.;
let y = (canvas |> Canvas.CanvasElement.height |> float_of_int) -. 30.;
Animation.render(canvas, x, 2., y, -2.);

