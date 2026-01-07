namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types
{
    /// <summary>
    /// Pane S/R/T transformation animation target element
    /// </summary>
    public enum AnimTargetElementPaneSrt
    {
        /// <summary>
        /// Translation x-component
        /// </summary>
        TransX,

        /// <summary>
        /// Translation y-component
        /// </summary>
        TransY,

        /// <summary>
        /// Translation z-component
        /// </summary>
        TransZ,

        /// <summary>
        /// Rotation x-component
        /// </summary>
        RotateX,

        /// <summary>
        /// Rotation y-component
        /// </summary>
        RotateY,

        /// <summary>
        /// Rotation z-component
        /// </summary>
        RotateZ,

        /// <summary>
        /// Scale x-component
        /// </summary>
        ScaleX,

        /// <summary>
        /// Scale y-component
        /// </summary>
        ScaleY,

        /// <summary>
        /// Size x-component (width)
        /// </summary>
        SizeX,

        /// <summary>
        /// Size y-component (height)
        /// </summary>
        SizeY,

        /// <summary>
        /// Opaqueness
        /// </summary>
        Alpha = 16
    }


    /// <summary>
    /// Pane visibility animation target element
    /// </summary>
    public enum AnimTargetElementPaneVis
    {
        /// <summary>
        /// Pane visibility
        /// </summary>
        Visiblility,
    }


    /// <summary>
    /// Vertex color animation target element
    /// </summary>
    public enum AnimTargetElementVtxClr
    {
        /// <summary>
        /// Top-left vertex color, red component
        /// </summary>
        LeftTop_R,

        /// <summary>
        /// Top-left vertex color, green component
        /// </summary>
        LeftTop_G,

        /// <summary>
        /// Top-left vertex color, blue component
        /// </summary>
        LeftTop_B,

        /// <summary>
        /// Top-left vertex color, alpha component
        /// </summary>
        LeftTop_A,

        /// <summary>
        /// Top-right vertex color, red component
        /// </summary>
        RightTop_R,

        /// <summary>
        /// Top-right vertex color, green component
        /// </summary>
        RightTop_G,

        /// <summary>
        /// Top-right vertex color, blue component
        /// </summary>
        RightTop_B,

        /// <summary>
        /// Top-right vertex color, alpha component
        /// </summary>
        RightTop_A,

        /// <summary>
        /// Bottom-left vertex color, red component
        /// </summary>
        LeftBottom_R,

        /// <summary>
        /// Bottom-left vertex color, green component
        /// </summary>
        LeftBottom_G,

        /// <summary>
        /// Bottom-left vertex color, blue component
        /// </summary>
        LeftBottom_B,

        /// <summary>
        /// Bottom-left vertex color, alpha component
        /// </summary>
        LeftBottom_A,

        /// <summary>
        /// Bottom-right vertex color, red component
        /// </summary>
        RightBottom_R,

        /// <summary>
        /// Bottom-right vertex color, green component
        /// </summary>
        RightBottom_G,

        /// <summary>
        /// Bottom-right vertex color, blue component
        /// </summary>
        RightBottom_B,

        /// <summary>
        /// Bottom-right vertex color, alpha component
        /// </summary>
        RightBottom_A,
    }


    /// <summary>
    /// Material color animation target element
    /// </summary>
    public enum AnimTargetElementMatClr
    {
        /// <summary>
        /// Material color, red component
        /// </summary>
        Material_R,

        /// <summary>
        /// Material color, green component
        /// </summary>
        Material_G,

        /// <summary>
        /// Material color, blue component
        /// </summary>
        Material_B,

        /// <summary>
        /// Material color, alpha component
        /// </summary>
        Material_A,

        /// <summary>
        /// TEV color register 0, red component
        /// </summary>
        Tev0_R,

        /// <summary>
        /// TEV color register 0, green component
        /// </summary>
        Tev0_G,

        /// <summary>
        /// TEV color register 0, blue component
        /// </summary>
        Tev0_B,

        /// <summary>
        /// TEV color register 0, alpha component
        /// </summary>
        Tev0_A,

        /// <summary>
        /// TEV color register 1, red component
        /// </summary>
        Tev1_R,

        /// <summary>
        /// TEV color register 1, green component
        /// </summary>
        Tev1_G,

        /// <summary>
        /// TEV color register 1, blue component
        /// </summary>
        Tev1_B,

        /// <summary>
        /// TEV color register 1, alpha component
        /// </summary>
        Tev1_A,

        /// <summary>
        /// TEV color register 2, red component
        /// </summary>
        Tev2_R,

        /// <summary>
        /// TEV color register 2, green component
        /// </summary>
        Tev2_G,

        /// <summary>
        /// TEV color register 2, blue component
        /// </summary>
        Tev2_B,

        /// <summary>
        /// TEV color register 2, alpha component
        /// </summary>
        Tev2_A,

        /// <summary>
        /// TEV constant color register 0, red component
        /// </summary>
        TevK0_R,

        /// <summary>
        /// TEV constant color register 0, green component
        /// </summary>
        TevK0_G,

        /// <summary>
        /// TEV constant color register 0, blue component
        /// </summary>
        TevK0_B,

        /// <summary>
        /// TEV constant color register 0, alpha component
        /// </summary>
        TevK0_A,

        /// <summary>
        /// TEV constant color register 1, red component
        /// </summary>
        TevK1_R,

        /// <summary>
        /// TEV constant color register 1, green component
        /// </summary>
        TevK1_G,

        /// <summary>
        /// TEV constant color register 1, blue component
        /// </summary>
        TevK1_B,

        /// <summary>
        /// TEV constant color register 1, alpha component
        /// </summary>
        TevK1_A,

        /// <summary>
        /// TEV constant color register 2, red component
        /// </summary>
        TevK2_R,

        /// <summary>
        /// TEV constant color register 2, green component
        /// </summary>
        TevK2_G,

        /// <summary>
        /// TEV constant color register 2, blue component
        /// </summary>
        TevK2_B,

        /// <summary>
        /// TEV constant color register 2, alpha component
        /// </summary>
        TevK2_A,

        /// <summary>
        /// TEV constant color register 3, red component
        /// </summary>
        TevK3_R,

        /// <summary>
        /// TEV constant color register 3, green component
        /// </summary>
        TevK3_G,

        /// <summary>
        /// TEV constant color register 3, blue component
        /// </summary>
        TevK3_B,

        /// <summary>
        /// TEV constant color register 3, alpha component
        /// </summary>
        TevK3_A,
    }


    /// <summary>
    /// Texture pattern animation target element
    /// </summary>
    public enum AnimTargetElementTexPat
    {
        /// <summary>
        /// Texture image
        /// </summary>
        Image
    }


    /// <summary>
    /// Texture S/R/T transformation animation target element
    /// </summary>
    public enum AnimTargetElementTexSrt
    {
        /// <summary>
        /// Translation x-component
        /// </summary>
        TransX,

        /// <summary>
        /// Translation y-component
        /// </summary>
        TransY,

        /// <summary>
        /// Rotation
        /// </summary>
        Rotate,

        /// <summary>
        /// Scale x-component
        /// </summary>
        ScaleX,

        /// <summary>
        /// Scale y-component
        /// </summary>
        ScaleY
    }
}
