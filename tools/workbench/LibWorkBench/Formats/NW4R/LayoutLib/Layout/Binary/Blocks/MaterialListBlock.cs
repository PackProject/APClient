using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout material list block
    /// </summary>
    [BinaryBlockProfile(signature: "mat1")]
    public class MaterialListBlock : TNW4RBinaryBlock<LayoutBinaryModel>
    {
        /// <summary>
        /// Size of this block's header when saved in binary form
        /// </summary>
        public const int HEADER_SIZE = 12;

        /// <summary>
        /// Material list
        /// </summary>
        public List<ResMaterial> Materials { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            // Material offsets are relative to the start of the block data
            ulong startOffset =
                reader.Position - NW4RBinaryBlockHeader.STRUCT_SIZE;

            ushort matNum = reader.ReadU16();
            reader.Align(4);

            List<uint> offsetList = new();
            for (uint i = 0; i < matNum; i++)
            {
                offsetList.Add(reader.ReadU32());
            }

            foreach (var it in offsetList)
            {
                reader.Seek((long)(startOffset + it), SeekOrigin.Begin);

                ResMaterial material = new();
                material.Read(reader);
                Materials.Add(material);
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            WorkMemWriter work = new(new BinaryCharEncoding(),
                                     writer.Endian);

            if (Materials.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many materials");
            }

            work.WriteU16((ushort)Materials.Count);
            work.Align(4);

            // Reserve space for offset table
            long offsetTablePos = (long)work.Position;
            work.WriteDebugFill((ulong)Materials.Count * sizeof(uint));

            // Calculate running offset for each material
            List<uint> offsetList = new();
            foreach (var it in Materials)
            {
                // Offset includes the data block header
                ulong offset = work.Position
                    + NW4RBinaryBlockHeader.STRUCT_SIZE;

                if (offset > uint.MaxValue)
                {
                    throw new FileBrokenException("Material list is too large");
                }

                offsetList.Add((uint)offset);
                it.Write(work);
            }

            // Go back and fix the offset table
            work.Seek(offsetTablePos, SeekOrigin.Begin);
            offsetList.ForEach(work.WriteU32);

            // Flush data to the real stream
            writer.Write(work.Buffer, work.Length);
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
            LayoutDataModel src = (LayoutDataModel)dataModel;

            Materials.Clear();
            HashSet<string> names = new();

            foreach (var it in src.Materials)
            {
                // Materials cannot have duplicate names
                if (names.Contains(it.Name))
                {
                    throw new FileBrokenException(
                        $"Duplicate material name: {it.Name}");
                }

                Materials.Add(ConvertMaterial(it));
            }
        }

        /// <summary>
        /// Converts a data-view material to its binary representation
        /// </summary>
        /// <param name="mat">Data-view material</param>
        /// <returns>Binary-view material</returns>
        private ResMaterial ConvertMaterial(Material mat)
        {
            ResMaterial res = new();

            res.Name = mat.Name;
            res.TevColors = mat.TevColors;
            res.TevKColors = mat.TevKColors;
            res.TexMaps = mat.TexMaps.Select(ConvertTexMap).ToList();
            res.TexSrts = mat.TexSrts;
            res.TexCoordGens = mat.TexCoordGens;
            res.TevSwapTable = mat.TevSwapTable;
            res.IndTexSrts = mat.IndTexSrts;
            res.IndStages = mat.IndStages;
            res.TevStages = mat.TevStages;
            res.AlphaCompare = mat.AlphaCompare;
            res.BlendMode = mat.BlendMode;
            res.ChanCtrl = mat.ChanCtrl;
            res.MaterialColor = mat.MaterialColor;

            return res;
        }

        /// <summary>
        /// Converts a data-view texture map to its binary representation
        /// </summary>
        /// <param name="texMap">Data-view texture map</param>
        /// <returns>Binary-view texture map</returns>
        /// <exception cref="FileBrokenException">Invalid texture was provided</exception>
        private ResTexMap ConvertTexMap(TexMap texMap)
        {
            ResTexMap res = new();

            TextureListBlock texList = Model!.GetOne<TextureListBlock>();

            int index = texList.Resources.FindIndex(
                it => it.Name == texMap.TextureName);

            if (index < 0)
            {
                throw new FileBrokenException(
                    $"Texture does not exist: {texMap.TextureName}");
            }

            res.TextureIndex = (ushort)index;
            res.WrapS = texMap.WrapS;
            res.WrapT = texMap.WrapT;

            return res;
        }
    }
}
