open Webapi;

/* Bindings to external JavaScript APIs */
let ballRadius = 10;
/* The main render function */
let rec render = (canvas , x, dx, y, dy) => {
  let ctx = Webapi.Canvas.CanvasElement.getContext2d(canvas);
  let square = x => x * x;
  let sum_sq = [1, 2, 3]->(Belt.List.map(square));
  Js.log(sum_sq);

  let width = canvas |> Canvas.CanvasElement.width |> float_of_int;
  let height = canvas |> Canvas.CanvasElement.height |> float_of_int;


  /* Clear the canvas */
  ctx->Webapi.Canvas.Canvas2d.clearRect(~x=0., ~y=0., ~w=width, ~h=height);

  /* Draw the ball */
  Webapi.Canvas.Canvas2d.beginPath(ctx);
  ctx->Webapi.Canvas.Canvas2d.arc(
    ~x=x +. dx,
    ~y=y +. dy,
    ~r=float_of_int(ballRadius),
    ~startAngle=0.,
    ~endAngle=2. *. Float.pi,
    ~anticw=false,
  );
  Webapi.Canvas.Canvas2d.setFillStyle(ctx, Webapi.Canvas.Canvas2d.String, "green");
  Webapi.Canvas.Canvas2d.fill(ctx);
  Webapi.Canvas.Canvas2d.closePath(ctx);

  /* Boundary detection and update positions */
  let newDx =
    if (x
        +. dx > width
        -. float_of_int(ballRadius)
        || x
        +. dx < float_of_int(ballRadius)) {
      -. dx;
    } else {
      dx;
    };
  let newDy =
    if (y
        +. dy > height
        -. float_of_int(ballRadius)
        || y
        +. dy < float_of_int(ballRadius)) {
      -. dy;
    } else {
      dy;
    };

  /* Request next animation frame */
  requestAnimationFrame((_) =>
    render(canvas, x +. newDx, newDx, y +. newDy, newDy)
  );
};
