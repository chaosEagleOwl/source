using System.Collections.Generic;

namespace AcGmsh
{
   public class LineG : IEntityG
   {
      public object Id { get; set; }
      public int P1 { get; private set; }
      public int P2 { get; private set; }
      public List<object> Parents { get; }
      public string GeoString { get => GetGeoString(); }

      public EntityGType Type => EntityGType.line;

      public LineG(int id, PointG pt1, PointG pt2)
      {
         Id = id;
         P1 = (int)pt1.Id;
         P2 = (int)pt2.Id;
      }

      private string GetGeoString()
      {
         return $"Line({Id}) = " + "{" + $"{P1}, {P2}" + "};";
      }
   }
}