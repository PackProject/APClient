using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary
{
    /// <summary>
    /// Material configuration (binary-view)
    /// </summary>
    public sealed class ResMaterial : IUseBinary
    {
        /// <summary>
        /// Material name
        /// </summary>
        public string Name { get; set; } = "";

        /// <summary>
        /// TEV color register settings
        /// </summary>
        public TevColorSet TevColors { get; set; } = new();

        /// <summary>
        /// TEV constant color register settings
        /// </summary>
        public TevKonstColorSet TevKColors { get; set; } = new();

        /// <summary>
        /// Texture map settings
        /// </summary>
        public List<ResTexMap> TexMaps { get; set; } = new();

        /// <summary>
        /// Texture S/R/T transformation settings
        /// </summary>
        public List<TexSrt> TexSrts { get; set; } = new();

        /// <summary>
        /// Texture coordinate generator settings
        /// </summary>
        public List<TexCoordGen> TexCoordGens { get; set; } = new();

        /// <summary>
        /// TEV color channel swap settings
        /// </summary>
        public TevSwapTable? TevSwapTable { get; set; } = null;

        /// <summary>
        /// Indirect texture S/R/T transformation settings
        /// </summary>
        public List<TexSrt> IndTexSrts { get; set; } = new();

        /// <summary>
        /// Indirect texture stages
        /// </summary>
        public List<IndirectStage> IndStages { get; set; } = new();

        /// <summary>
        /// TEV stages
        /// </summary>
        public List<TevStage> TevStages { get; set; } = new();

        /// <summary>
        /// Visibility test
        /// </summary>
        public AlphaCompare? AlphaCompare { get; set; } = null;

        /// <summary>
        /// Blend mode settings
        /// </summary>
        public BlendMode? BlendMode { get; set; } = null;

        /// <summary>
        /// Channel control settings
        /// </summary>
        public ChanCtrl? ChanCtrl { get; set; } = null;

        /// <summary>
        /// Material color (GX_COLOR0A0)
        /// </summary>
        public GXColor? MaterialColor { get; set; } = null;

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            Name = reader.ReadString(
                maxlen: LayoutDefine.MAT_NAME_LEN,
                exact: true
            );

            TevColors.Read(reader);
            TevKColors.Read(reader);

            // Resource num describes how the variable data looks
            MaterialResourceNum resNum = new();
            resNum.Read(reader);

            for (uint i = 0; i < resNum.TexMapNum; i++)
            {
                ResTexMap texMap = new();
                texMap.Read(reader);
                TexMaps.Add(texMap);
            }

            for (uint i = 0; i < resNum.TexSrtNum; i++)
            {
                TexSrt texSrt = new();
                texSrt.Read(reader);
                TexSrts.Add(texSrt);
            }

            for (uint i = 0; i < resNum.TexCoordGenNum; i++)
            {
                TexCoordGen texCoordGen = new();
                texCoordGen.Read(reader);
                TexCoordGens.Add(texCoordGen);
            }

            if (resNum.HasChanCtrl)
            {
                ChanCtrl = new();
                ChanCtrl.Read(reader);
            }

            if (resNum.HasMatColor)
            {
                MaterialColor = new();
                MaterialColor.Read(reader);
            }

            if (resNum.HasTevSwapTable)
            {
                TevSwapTable = new();
                TevSwapTable.Read(reader);
            }

            for (uint i = 0; i < resNum.IndTexSrtNum; i++)
            {
                TexSrt indTexSrt = new();
                indTexSrt.Read(reader);
                IndTexSrts.Add(indTexSrt);
            }

            for (uint i = 0; i < resNum.IndStageNum; i++)
            {
                IndirectStage indStage = new();
                indStage.Read(reader);
                IndStages.Add(indStage);
            }

            for (uint i = 0; i < resNum.TevStageNum; i++)
            {
                TevStage tevStage = new();
                tevStage.Read(reader);
                TevStages.Add(tevStage);
            }

            if (resNum.HasAlphaCompare)
            {
                AlphaCompare = new();
                AlphaCompare.Read(reader);
            }

            if (resNum.HasBlendMode)
            {
                BlendMode = new();
                BlendMode.Read(reader);
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            writer.WriteString(
                Name,
                maxlen: LayoutDefine.MAT_NAME_LEN,
                terminate: false,
                exact: true
            );

            TevColors.Write(writer);
            TevKColors.Write(writer);

            // Resource num describes how the variable data looks
            MaterialResourceNum resNum = new();
            resNum.TexMapNum = (byte)TexMaps.Count;
            resNum.TexSrtNum = (byte)TexSrts.Count;
            resNum.TexCoordGenNum = (byte)TexCoordGens.Count;
            resNum.HasTevSwapTable = TevSwapTable != null;
            resNum.IndTexSrtNum = (byte)IndTexSrts.Count;
            resNum.IndStageNum = (byte)IndStages.Count;
            resNum.TevStageNum = (byte)TevStages.Count;
            resNum.HasAlphaCompare = AlphaCompare != null;
            resNum.HasBlendMode = BlendMode != null;
            resNum.HasChanCtrl = ChanCtrl != null;
            resNum.HasMatColor = MaterialColor != null;
            resNum.Write(writer);

            TexMaps.ForEach(it => it.Write(writer));
            TexSrts.ForEach(it => it.Write(writer));
            TexCoordGens.ForEach(it => it.Write(writer));

            if (TevSwapTable != null)
            {
                TevSwapTable.Write(writer);
            }

            IndTexSrts.ForEach(it => it.Write(writer));
            IndStages.ForEach(it => it.Write(writer));
            TevStages.ForEach(it => it.Write(writer));

            if (AlphaCompare != null)
            {
                AlphaCompare.Write(writer);
            }

            if (BlendMode != null)
            {
                BlendMode.Write(writer);
            }

            if (ChanCtrl != null)
            {
                ChanCtrl.Write(writer);
            }

            if (MaterialColor != null)
            {
                MaterialColor.Write(writer);
            }
        }
    }
}
